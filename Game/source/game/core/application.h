#pragma once
#include "engine/core/main_window/main_window.h"
#include "engine/core/message/message_bus.h"
#include "engine/time/time_manager/time_manager.h"

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

		void handle_events();
		void handle_messages();
		void update();
		void render();

	private:
		std::unique_ptr<core::MainWindow> m_window;
		std::unique_ptr<core::MessageBus> m_message_bus;
		std::unique_ptr<time::TimeManager> m_time_manager;

		bool m_running{ true };
	};
}