#pragma once
#include <cstdint>
#include "engine/utility/enum.h"

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
		return static_cast<Modifier>(utility::to_underlying(_left) | utility::to_underlying(_right));
	}

	constexpr inline Modifier operator&(Modifier _left, Modifier _right)
	{
		return static_cast<Modifier>(utility::to_underlying(_left) & utility::to_underlying(_right));
	}

	constexpr inline bool has_flag(Modifier _value, Modifier _flag)
	{
		return (utility::to_underlying(_value) & utility::to_underlying(_flag)) != 0;
	}
}