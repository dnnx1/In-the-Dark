#pragma once
#include <variant>

namespace itd::core
{
	struct CloseGameRequestMessage {};
	struct CloseGameMessage {};

	using Message = std::variant<
		std::monostate,
		CloseGameRequestMessage,
		CloseGameMessage
	>;
}