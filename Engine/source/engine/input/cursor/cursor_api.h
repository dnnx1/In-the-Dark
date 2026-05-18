#pragma once
#include "external/glm/vec2.hpp"

namespace itd::input
{
	class CursorAPI
	{
	public:
		virtual ~CursorAPI() = default;

	public:
		virtual glm::vec2 position() const = 0;
	};
}