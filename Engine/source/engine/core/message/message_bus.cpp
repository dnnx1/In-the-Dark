#include "engine/engine_api.h"
#include "engine/core/message/message_bus.h"

itd::core::MessageBus::MessageBus()
{
	EngineAPI::instance().message_bus = this;
}

itd::core::MessageBus::~MessageBus()
{
	if (EngineAPI::instance().message_bus == this)
		EngineAPI::instance().message_bus = nullptr;
}

std::unique_ptr<itd::core::MessageBus> itd::core::MessageBus::make_unique()
{
	return std::make_unique<MessageBus>();
}

void itd::core::MessageBus::send(Message&& _message)
{
	m_polling ? m_pending_messages.push(std::move(_message)) : m_messages.push(std::move(_message));
}
