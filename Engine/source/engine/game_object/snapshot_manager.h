#pragma once
#include <unordered_map>
#include <memory>
#include "engine/game_object/snapshot_storage.h"

namespace itd::game_object
{
	class SnapshotManager
	{
	private:
		using StoragePtr = std::unique_ptr<ISnapshotStorage>;

	public:
		SnapshotManager() = default;
		~SnapshotManager() = default;

		SnapshotManager(const SnapshotManager&) = delete;
		SnapshotManager(SnapshotManager&&) = default;

		SnapshotManager& operator=(const SnapshotManager&) = delete;
		SnapshotManager& operator=(SnapshotManager&&) = default;

	public:
		static std::shared_ptr<SnapshotManager> make_shared()
		{
			return std::make_shared<SnapshotManager>();
		}

	public:
		template <typename Snapshot> SnapshotStorage<Snapshot>& storage()
		{
			auto type_id = SnapshotStorageTypeID::get<Snapshot>();
			auto it = m_storages.find(type_id);
			if (it == m_storages.end())
			{
				auto storage = std::make_unique<SnapshotStorage<Snapshot>>();
				auto* ptr = storage.get();
				m_storages.emplace(type_id, std::move(storage));
				return *ptr;
			}
			return *static_cast<SnapshotStorage<Snapshot>*>(it->second.get());
		}

		template <typename Snapshot> bool exists() const
		{
			auto type_id = SnapshotStorageTypeID::get<Snapshot>();
			return m_storages.find(type_id) != m_storages.end();
		}

	private:
		std::unordered_map<uint32_t, StoragePtr> m_storages;
	};
}