#pragma once
#include "in_the_dark/core/main_window/main_window.h"
#include "in_the_dark/core/message/message_bus.h"
#include "in_the_dark/core/worker/worker_thread.h"
#include "in_the_dark/core/worker/main_thread_worker.h"
#include "in_the_dark/core/worker/async_worker.h"
#include "in_the_dark/core/worker/deferred_async_worker.h"
#include "in_the_dark/graphics/graphics/graphics.h"
#include "in_the_dark/graphics/renderer/renderer.h"
#include "in_the_dark/time/time_manager/time_manager.h"
#include "in_the_dark/input/keyboard/keyboard.h"
#include "in_the_dark/input/mouse/mouse.h"
#include "in_the_dark/input/cursor/cursor.h"
#include "in_the_dark/scene/scene_manager/scene_manager.h"

namespace itd
{
	class Application
	{
	public:
		Application() = default;
		~Application() = default;

		Application(const Application&) = delete;
		Application(Application&&) = delete;

		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

	public:
		void run(int _argc, char* _argv[]);

	private:
		void initialize(int _argc, char* _argv[]);
		void terminate();
		void loop();

		void begin_frame();
		void handle_events();
		void handle_messages();
		void update();
		void render();
		void end_frame();

	private:
		std::unique_ptr<core::MainWindow> m_window;
		std::unique_ptr<core::MessageBus> m_message_bus;
		std::shared_ptr<core::WorkerThread> m_worker_thread;
		std::unique_ptr<core::MainThreadWorker> m_main_thread_worker;
		std::unique_ptr<core::AsyncWorker> m_async_worker;
		std::unique_ptr<core::DeferredAsyncWorker> m_deferred_async_worker;
		std::unique_ptr<graphics::Graphics> m_graphics;
		std::unique_ptr<graphics::Renderer> m_renderer;
		std::unique_ptr<time::TimeManager> m_time_manager;

		std::unique_ptr<input::Keyboard> m_keyboard;
		std::unique_ptr<input::Mouse> m_mouse;
		std::unique_ptr<input::Cursor> m_cursor;

		std::unique_ptr<scene::SceneManager> m_scene_manager;

		bool m_running{ true };
	};
}