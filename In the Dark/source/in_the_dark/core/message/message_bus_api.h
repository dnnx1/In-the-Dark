#pragma once
#include "in_the_dark/core/message/message.h"

namespace itd::core
{
	class MessageBusAPI
	{
	public:
		virtual ~MessageBusAPI() = default;

	public:
		virtual void send(Message&& _message) = 0;
	};
}