#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "engine/world/internal/object_storage.h"
#include "engine/world/internal/object.h"
#include "engine/utility/hierarchy_id_manager.h"

namespace itd::world
{
	class World
	{
	public:
		World() = default;
		~World() = default;

		World(const World&) = delete;
		World(World&&) = default;

		World& operator=(const World&) = delete;
		World& operator=(World&&) = default;

	public:
		template <typename ObjectType> ObjectStorageAPI<ObjectType>& storage() { return *get_or_create_storage<ObjectType>(); }

	private:
		template <typename ObjectType> ObjectStorage<ObjectType>* get_or_create_storage()
		{
			static_assert(std::is_base_of_v<Object, ObjectType>, "ObjectType must inherit from Object");
			auto type_id = utility::HierarchyIDManager<IObjectStorage>::get<ObjectType>();
			auto it = m_object_storages.find(type_id);
			if (it == m_object_storages.end())
			{
				auto object_storage = std::make_unique<ObjectStorage<ObjectType>>();
				auto* ptr = object_storage.get();
				m_object_storages.emplace(type_id, std::move(object_storage));
				return ptr;
			}
			return static_cast<ObjectStorage<ObjectType>*>(it->second.get());
		}

	public:
		void apply_pending_changes()
		{
			for (auto& [type_id, object_storage] : m_object_storages)
				object_storage->apply_pending_changes();
		}

		void deserialize(const json& _root)
		{

		}

		json serialize() const
		{

		}

	private:
		std::unordered_map<uint32_t, std::unique_ptr<IObjectStorage>> m_object_storages;
	};
}