#include "engine/core/error.h"
#include "game/core/application.h"

void itd::Application::run(int _argc, char* _argv[])
{
	try
	{
		initialize(_argc, _argv);
		loop();
		terminate();
	}
	catch (const core::Error& _e) {}
	catch (const std::exception& _e) {}
}

void itd::Application::initialize(int _argc, char* _argv[])
{
	// === Creation ===
	m_window = core::MainWindow::make_unique(960, 640, "In the Dark");
	m_message_bus = core::MessageBus::make_unique();
	m_time_manager = time::TimeManager::make_unique(1.0f / 30.0f);

	// === Preparation ===
	m_window->vsync(false);
	m_time_manager->set_framerate(60);
}

void itd::Application::terminate()
{
}

void itd::Application::loop()
{
	m_time_manager->prepare_to_game_loop();
	while (m_running)
	{
		m_time_manager->begin_frame();

		handle_events();
		handle_messages();

		m_time_manager->update();

		update();
		render();

		m_time_manager->end_frame();
	}
}

void itd::Application::handle_events()
{
	m_window->poll_events([&](const core::Event& _event)
		{
			if (std::holds_alternative<core::WindowCloseEvent>(_event))
			{
				// TODO later close popup
				m_message_bus->send(core::CloseGameMessage{});
			}
		});
}

void itd::Application::handle_messages()
{
	m_message_bus->poll_messages([&](const core::Message& _message)
		{
			if (std::holds_alternative<core::CloseGameMessage>(_message))
			{
				m_running = false;
			}
		});
}

void itd::Application::update()
{
}

void itd::Application::render()
{
}
