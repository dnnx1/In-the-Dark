#pragma once
#include "external/glm/vec2.hpp"

namespace itd::game_object
{
	class Obstacle
	{
	public:
		struct Snapshot
		{
			glm::vec2 position{ 0.0f };

			glm::ivec2 collider_offset{ 0 };
			glm::ivec2 collider_size{ 0 };
		};

	public:
		Obstacle(const Snapshot& _snapshot);
		Obstacle() = default;
		~Obstacle() = default;

		Obstacle(const Obstacle&) = default;
		Obstacle(Obstacle&&) = default;

		Obstacle& operator=(const Obstacle&) = default;
		Obstacle& operator=(Obstacle&&) = default;

	public:
		Snapshot make_snapshot() const;

	private:
		glm::vec2 m_prev_position{ 0.0f };
		glm::vec2 m_curr_position{ 0.0f };

		glm::ivec2 m_collider_offset{ 0.0f };
		glm::ivec2 m_collider_size{ 0.0f };
	};
}