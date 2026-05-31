#pragma once
#include <variant>

namespace itd::core
{
	struct CloseGameRequestMessage {};
	struct CloseGameMessage {};
	struct BuildCompletedMessage {};

	using Message = std::variant<
		std::monostate,
		CloseGameRequestMessage,
		CloseGameMessage,
		BuildCompletedMessage
	>;

	template <typename MessageType> inline bool message_is(const Message& _message)
	{
		return std::holds_alternative<MessageType>(_message);
	}

	template <typename MessageType> inline const MessageType* message_try_cast(const Message& _message)
	{
		return std::get_if<MessageType>(&_message);
	}
}