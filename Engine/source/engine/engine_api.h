#pragma once
#include "engine/core/main_window/main_window_api.h"
#include "engine/core/message/message_bus_api.h"
#include "engine/core/worker/worker_api.h"
#include "engine/graphics/graphics/graphics_api.h"
#include "engine/graphics/renderer/renderer_api.h"
#include "engine/time/time_manager/time_manager_api.h"
#include "engine/input/keyboard/keyboard_api.h"
#include "engine/input/mouse/mouse_api.h"
#include "engine/input/cursor/cursor_api.h"
#include "engine/scene/scene_manager/scene_manager_api.h"

namespace itd
{
	struct EngineAPI
	{
		static EngineAPI& instance() { static EngineAPI api; return api; }

		core::MainWindowAPI* window{ nullptr };
		core::MessageBusAPI* message_bus{ nullptr };
		core::WorkerAPI* main_thread_worker{ nullptr };
		core::WorkerAPI* async_worker{ nullptr };
		graphics::GraphicsAPI* graphics{ nullptr };
		graphics::RendererAPI* renderer{ nullptr };
		time::TimeManagerAPI* time_manager{ nullptr };

		input::KeyboardAPI* keyboard{ nullptr };
		input::MouseAPI* mouse{ nullptr };
		input::CursorAPI* cursor{ nullptr };

		scene::SceneManagerAPI* scenes{ nullptr };
	};
}