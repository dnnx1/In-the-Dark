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
	m_window = core::MainWindow::make_unique(960, 640, "In the Dark");
}

void itd::Application::terminate()
{
}

void itd::Application::loop()
{
	while (m_running)
	{
		handle_events();
		handle_messages();

		update();
		render();

		m_running = !m_window->should_close();
	}
}

void itd::Application::handle_events()
{
	m_window->poll_events([&](const core::Event& _event)
		{
			if (std::holds_alternative<core::WindowCloseEvent>(_event))
			{
				// TODO later close popup
				m_window->set_should_close(false);
			}
		});
}

void itd::Application::handle_messages()
{
}

void itd::Application::update()
{
}

void itd::Application::render()
{
}
