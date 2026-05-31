#include "engine/game_object/game_object_manager.h"
#include "engine/game_object/game_object_list.h"

std::shared_ptr<itd::game_object::SnapshotManager> itd::game_object::GameObjectManager::make_snapshot()
{
	auto snapshot = std::make_shared<SnapshotManager>();

#define REGISTER_GAME_OBJECT(GameObject) \
	if (exists<GameObject>()) \
	{ \
		for (auto& elem : storage<GameObject>()) \
		{ \
			snapshot->storage<GameObject::Snapshot>().push_back(elem.make_snapshot()); \
		} \
	}

	GAME_OBJECT_LIST
#undef REGISTER_GAME_OBJECT

	return snapshot;
}

void itd::game_object::GameObjectManager::rebuild_by_snapshot(std::shared_ptr<SnapshotManager> _snapshot)
{
	m_storages.clear();

#define REGISTER_GAME_OBJECT(GameObject) \
	if (_snapshot->exists<GameObject::Snapshot>()) \
	{ \
		for (auto& elem : _snapshot->storage<GameObject ## ::Snapshot>()) \
		{ \
			storage<GameObject>().emplace(elem); \
		} \
	}

	GAME_OBJECT_LIST
#undef REGISTER_GAME_OBJECT
}
