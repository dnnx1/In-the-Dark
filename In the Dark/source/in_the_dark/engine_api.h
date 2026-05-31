#pragma once
#include "in_the_dark/core/main_window/main_window_api.h"
#include "in_the_dark/core/message/message_bus_api.h"
#include "in_the_dark/core/worker/worker_api.h"
#include "in_the_dark/graphics/graphics/graphics_api.h"
#include "in_the_dark/graphics/renderer/renderer_api.h"
#include "in_the_dark/graphics/shader/shader_manager_api.h"
#include "in_the_dark/time/time_manager/time_manager_api.h"
#include "in_the_dark/input/keyboard/keyboard_api.h"
#include "in_the_dark/input/mouse/mouse_api.h"
#include "in_the_dark/input/cursor/cursor_api.h"
#include "in_the_dark/scene/scene_manager/scene_manager_api.h"

namespace itd
{
	struct EngineAPI
	{
		static EngineAPI& instance() { static EngineAPI api; return api; }

		core::MainWindowAPI* window{ nullptr };
		core::MessageBusAPI* message_bus{ nullptr };
		core::WorkerAPI* main_thread_worker{ nullptr };
		core::WorkerAPI* async_worker{ nullptr };
		core::WorkerAPI* deferred_async_worker{ nullptr };
		graphics::GraphicsAPI* graphics{ nullptr };
		graphics::RendererAPI* renderer{ nullptr };
		time::TimeManagerAPI* time_manager{ nullptr };

		graphics::ShaderManagerAPI* shaders{ nullptr };

		input::KeyboardAPI* keyboard{ nullptr };
		input::MouseAPI* mouse{ nullptr };
		input::CursorAPI* cursor{ nullptr };

		scene::SceneManagerAPI* scenes{ nullptr };
	};
}