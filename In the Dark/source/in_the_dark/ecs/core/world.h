#pragma once
#include <unordered_map>
#include <queue>
#include <memory>
#include "in_the_dark/ecs/core/archetype.h"

namespace itd::ecs
{
	class World
	{
	public:
		World() = default;
		~World() = default;

		World(const World&) = delete;
		World(World&&) = delete;

		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;

	public:
		template <typename ...Components> Entity create_entity(Components&& ..._components)
		{
			Signature signature;
			(signature.set(ComponentStorageTypeID::get<std::decay_t<Components>>()), ...);

			auto it = m_archetypes.find(signature);
			if (it == m_archetypes.end())
			{
				auto archetype = Archetype::create<std::decay_t<Components>...>();
				it = m_archetypes.emplace(signature, std::move(archetype)).first;
			}

			Entity entity;
			if (m_free_list.empty())
			{
				entity = m_entity_counter++;
			}
			else
			{
				entity = m_free_list.front();
				m_free_list.pop();
			}

			it->second->add_entity(entity, std::forward<Components>(_components)...);
			return entity;
		}

		template <typename ...Components, typename Func> void for_each(Func&& _func)
		{
			Signature signature;
			(signature.set(ComponentStorageTypeID::get<std::decay_t<Components>>()), ...);

			for (auto& [s, archetype] : m_archetypes)
			{
				if ((s & signature) != signature) continue;
				archetype->for_each<Func, std::decay_t<Components>...>(std::forward<Func>(_func));
			}
		}

	private:
		std::unordered_map<Signature, std::unique_ptr<Archetype>> m_archetypes;

		Entity m_entity_counter{ 0 };
		std::queue<Entity> m_free_list;
	};
}