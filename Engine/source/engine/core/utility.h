#pragma once
#include <type_traits>

namespace itd::core
{
	template <typename Type> constexpr inline auto to_underlying(Type _value)
	{
		return static_cast<std::underlying_type_t<Type>>(_value);
	}
}