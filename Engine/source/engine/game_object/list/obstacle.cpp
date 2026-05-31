#include "engine/game_object/list/obstacle.h"

itd::game_object::Obstacle::Obstacle(const Snapshot& _snapshot)
{
	m_prev_position = m_curr_position = _snapshot.position;

	m_collider_offset = _snapshot.collider_offset;
	m_collider_size = _snapshot.collider_size;
}

itd::game_object::Obstacle::Snapshot itd::game_object::Obstacle::make_snapshot() const
{
	Snapshot snapshot;

	snapshot.position = m_curr_position;

	snapshot.collider_offset = m_collider_offset;
	snapshot.collider_size = m_collider_size;

	return snapshot;
}
