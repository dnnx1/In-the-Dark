#pragma once
#include <unordered_map>
#include <memory>
#include "in_the_dark/game_object/game_object_storage.h"
#include "in_the_dark/game_object/snapshot_manager.h"

namespace itd::game_object
{
	class GameObjectManager
	{
	private:
		using StoragePtr = std::unique_ptr<IGameObjectStorage>;

	public:
		GameObjectManager() = default;
		~GameObjectManager() = default;

		GameObjectManager(const GameObjectManager&) = delete;
		GameObjectManager(GameObjectManager&&) = default;

		GameObjectManager& operator=(const GameObjectManager&) = delete;
		GameObjectManager& operator=(GameObjectManager&&) = default;

	public:
		template <typename GameObject> GameObjectStorage<GameObject>& storage()
		{
			auto type_id = GameObjectStorageTypeID::get<GameObject>();
			auto it = m_storages.find(type_id);
			if (it == m_storages.end())
			{
				auto storage = std::make_unique<GameObjectStorage<GameObject>>();
				auto* ptr = storage.get();
				m_storages.emplace(type_id, std::move(storage));
				return *ptr;
			}
			return *static_cast<GameObjectStorage<GameObject>*>(it->second.get());
		}

		template <typename GameObject> bool exists() const
		{
			auto type_id = GameObjectStorageTypeID::get<GameObject>();
			return m_storages.find(type_id) != m_storages.end();
		}

	public:
		std::shared_ptr<SnapshotManager> make_snapshot();
		void rebuild_by_snapshot(std::shared_ptr<SnapshotManager> _snapshot);

	private:
		std::unordered_map<uint32_t, StoragePtr> m_storages;
	};
}