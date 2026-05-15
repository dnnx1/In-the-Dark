#pragma once
#include "engine/core/main_window/main_window_api.h"

namespace itd::core
{
	struct EngineAPI
	{
		static EngineAPI& instance() { static EngineAPI api; return api; }

		MainWindowAPI* window{ nullptr };
	};
}