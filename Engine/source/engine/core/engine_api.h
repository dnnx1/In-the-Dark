#pragma once
#include "engine/core/main_window/main_window_api.h"
#include "engine/core/message/message_bus_api.h"
#include "engine/time/time_manager/time_manager_api.h"

namespace itd::core
{
	struct EngineAPI
	{
		static EngineAPI& instance() { static EngineAPI api; return api; }

		MainWindowAPI* window{ nullptr };
		MessageBusAPI* message_bus{ nullptr };
		time::TimeManagerAPI* time_manager{ nullptr };
	};
}