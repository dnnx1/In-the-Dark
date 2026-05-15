#pragma once
#include <cstdint>

namespace itd::input
{
	enum class MouseCode : uint8_t
	{
		Undefined,

		Left,
		Right,
		Middle,

		__count
	};
}