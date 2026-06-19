#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <assert.h>
#include "in_the_dark/ecs/core/common.h"
#include "in_the_dark/ecs/core/component_storage.h"

namespace itd::ecs
{
	class Archetype
	{
	private:
		using StoragePtr = std::unique_ptr<IComponentStorage>;

	public:
		Archetype() : m_storages(MAX_COMPONENTS) {}
		~Archetype() = default;

		Archetype(const Archetype&) = delete;
		Archetype(Archetype&&) = default;

		Archetype& operator=(const Archetype&) = delete;
		Archetype& operator=(Archetype&&) = default;

	public:
		template <typename ...Components> static std::unique_ptr<Archetype> create()
		{
			auto archetype = std::make_unique<Archetype>();
			(archetype->register_storage<Components>(), ...);
			return archetype;
		}

	public:
		template <typename ...Components> void add_entity(Entity _entity, Components&& ..._components)
		{
			assert(std::find(m_entities.begin(), m_entities.end(), _entity) == m_entities.end());
			m_entities.push_back(_entity);
			(add_component(std::forward<Components>(_components)), ...);
		}

		template <typename Func, typename ...Components> void for_each(Func&& _func)
		{
			auto storages = std::tuple<ComponentStorage<Components>*...>
				(
					static_cast<ComponentStorage<Components>*>(m_storages[ComponentStorageTypeID::get<Components>()].get())...
				);

			for (size_t i = 0; i < m_entities.size(); i++)
			{
				std::apply([&](auto* ..._storage)
					{
						_func(_storage->components[i]...);
					}, storages);
			}
		}

		const Signature& signature() const { return m_signature; }

	private:
		template <typename Component> void register_storage()
		{
			auto type_id = ComponentStorageTypeID::get<Component>();
			if (m_storages[type_id] && m_signature[type_id]) return;

			m_storages[type_id] = std::make_unique<ComponentStorage<Component>>();
			m_signature.set(type_id);
		}

		template <typename Component> void add_component(Component&& _component)
		{
			using Decayed = std::decay_t<Component>;
			uint32_t type_id = ComponentStorageTypeID::get<Decayed>();
			auto* storage = static_cast<ComponentStorage<Decayed>*>(m_storages[type_id].get());
			assert(storage);
			storage->components.push_back(std::forward<Component>(_component));
		}

	private:
		std::vector<Entity> m_entities;
		std::vector<StoragePtr> m_storages;
		Signature m_signature;
	};
}