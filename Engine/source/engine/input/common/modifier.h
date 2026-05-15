#pragma once
#include <cstdint>
#include "engine/core/utility.h"

namespace itd::input
{
	enum class Modifier : uint8_t
	{
		None = 0,
		Shift = 1 << 0,
		Control = 1 << 1,
		Alt = 1 << 2,
		Super = 1 << 3
	};

	constexpr inline Modifier operator|(Modifier _left, Modifier _right)
	{
		return static_cast<Modifier>(core::to_underlying(_left) | core::to_underlying(_right));
	}

	constexpr inline Modifier operator&(Modifier _left, Modifier _right)
	{
		return static_cast<Modifier>(core::to_underlying(_left) & core::to_underlying(_right));
	}

	constexpr inline bool has_flag(Modifier _value, Modifier _flag)
	{
		return (core::to_underlying(_value) & core::to_underlying(_flag)) != 0;
	}
}