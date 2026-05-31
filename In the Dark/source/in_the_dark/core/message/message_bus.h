#pragma once
#include <memory>
#include <queue>
#include "in_the_dark/core/message/message_bus_api.h"

namespace itd::core
{
	class MessageBus : public MessageBusAPI
	{
	public:
		MessageBus();
		~MessageBus();

		MessageBus(const MessageBus&) = delete;
		MessageBus(MessageBus&&) = delete;

		MessageBus& operator=(const MessageBus&) = delete;
		MessageBus& operator=(MessageBus&&) = delete;

	public:
		static std::unique_ptr<MessageBus> make_unique();

	public:
		template <typename Func> void poll_messages(Func&& _func)
		{
			m_polling = true;
			while (!m_messages.empty())
			{
				_func(m_messages.front());
				m_messages.pop();
			}
			m_polling = false;
			if (!m_pending_messages.empty())
				m_messages.swap(m_pending_messages);
		}

	public:
		void send(Message&& _message) override;

	private:
		std::queue<Message> m_messages;
		std::queue<Message> m_pending_messages;
		bool m_polling{ false };
	};
}