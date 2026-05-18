#pragma once
#include "engine/core/main_window/main_window_api.h"
#include "engine/core/message/message_bus_api.h"
#include "engine/graphics/graphics/graphics_api.h"
#include "engine/graphics/renderer/renderer_api.h"
#include "engine/time/time_manager/time_manager_api.h"
#include "engine/input/keyboard/keyboard_api.h"

namespace itd::core
{
	struct EngineAPI
	{
		static EngineAPI& instance() { static EngineAPI api; return api; }

		MainWindowAPI* window{ nullptr };
		MessageBusAPI* message_bus{ nullptr };
		graphics::GraphicsAPI* graphics{ nullptr };
		graphics::RendererAPI* renderer{ nullptr };
		time::TimeManagerAPI* time_manager{ nullptr };

		input::KeyboardAPI* keyboard{ nullptr };
	};
}