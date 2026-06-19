#pragma once
#include "external/glm/vec2.hpp"

namespace itd::game_object
{
	struct Collider
	{
		enum class Type : uint8_t
		{
			Static,
			Dynamic,
			Trigger,
		};

		glm::vec2 position{ 0.0f };
		glm::vec2 size{ 0.0f };
		Type type{ Type::Static };
	};
}