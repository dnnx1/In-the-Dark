#pragma once
#include <cstdint>
#include <limits>
#include <bitset>

namespace itd::ecs
{
	using Entity = uint32_t;
	inline constexpr Entity DUMMY_ENTITY = std::numeric_limits<uint32_t>::max();

	inline constexpr uint32_t MAX_COMPONENTS = 32;
	using Signature = std::bitset<MAX_COMPONENTS>;
}