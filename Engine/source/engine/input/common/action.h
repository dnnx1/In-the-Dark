#pragma once
#include <cstdint>

namespace itd::input
{
	enum class Action : uint8_t
	{
		Undefined,

		Press,
		Release,
	};
}