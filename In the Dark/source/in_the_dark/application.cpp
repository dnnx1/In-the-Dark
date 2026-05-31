#include "in_the_dark/error.h"
#include "in_the_dark/application.h"
#include "in_the_dark/input/frame_counter.h"
#include "in_the_dark/scene/building/building_scene.h"

void itd::Application::run(int _argc, char* _argv[])
{
	try
	{
		initialize(_argc, _argv);
		loop();
		terminate();
	}
	catch (const Error& _e) {}
	catch (const std::exception& _e) {}
}

void itd::Application::initialize(int _argc, char* _argv[])
{
	// === Creation ===
	m_window = core::MainWindow::make_unique(960, 640, "In the Dark");
	m_message_bus = core::MessageBus::make_unique();
	m_worker_thread = core::WorkerThread::make_shared();
	m_main_thread_worker = core::MainThreadWorker::make_unique();
	m_async_worker = core::AsyncWorker::make_unique(m_worker_thread);
	m_deferred_async_worker = core::DeferredAsyncWorker::make_unique(m_worker_thread);
	m_graphics = graphics::Graphics::make_unique();
	m_renderer = graphics::Renderer::make_unique();
	m_time_manager = time::TimeManager::make_unique(2.0f / 60.0f);

	m_shaders = graphics::ShaderManager::make_unique();

	m_keyboard = input::Keyboard::make_unique();
	m_mouse = input::Mouse::make_unique();
	m_cursor = input::Cursor::make_unique();

	m_scene_manager = scene::SceneManager::make_unique();

	// === Scenes creation ===
	m_scene_manager->create_scene<scene::BuildingScene>();

	// === Preparation ===
	m_window->vsync(false);
	m_time_manager->set_framerate(60);
	m_graphics->set_viewport(0, 0, m_window->framebuffer_size().x, m_window->framebuffer_size().y);
	m_scene_manager->push_scene(scene::SceneTypeID::get<scene::BuildingScene>());
}

void itd::Application::terminate()
{
	m_scene_manager->destroy_scenes();
	m_worker_thread->stop();
}

void itd::Application::loop()
{
	m_time_manager->prepare_to_game_loop();
	while (m_running)
	{
		begin_frame();
		handle_events();
		handle_messages();
		update();
		render();
		end_frame();
	}
}

void itd::Application::begin_frame()
{
	m_time_manager->begin_frame();
	input::FrameCounter::value++;
	m_main_thread_worker->execute();
	m_deferred_async_worker->dispatch();
}

void itd::Application::handle_events()
{
	m_window->poll_events([&](const core::Event& _event)
		{
			if (core::event_is<core::WindowCloseEvent>(_event))
			{
				// TODO later close popup
				m_message_bus->send(core::CloseGameMessage{});
			}
			else if (auto* evt = core::event_try_cast<core::KeyEvent>(_event))
			{
				m_keyboard->set(evt->code, evt->action);
			}
			else if (auto* evt = core::event_try_cast<core::MouseButtonEvent>(_event))
			{
				m_mouse->set(evt->code, evt->action);
			}
			else if (auto* evt = core::event_try_cast<core::CursorPosEvent>(_event))
			{
				m_cursor->set_position(evt->position);
			}
		});
}

void itd::Application::handle_messages()
{
	m_message_bus->poll_messages([&](const core::Message& _message)
		{
			if (core::message_is<core::CloseGameMessage>(_message))
			{
				m_running = false;
			}
			else if (core::message_is<core::BuildCompletedMessage>(_message))
			{
				// TODO setup after build
			}

			m_scene_manager->handle_messages(_message);
		});
}

void itd::Application::update()
{
	m_time_manager->update();

	m_scene_manager->pre_update(m_time_manager->delta_time());
	m_time_manager->fixed_loop([&](float _fixed_dt) {m_scene_manager->fixed_update(_fixed_dt); });
	m_scene_manager->post_update(m_time_manager->delta_time());

	// temp for debug
	if (m_keyboard->just_pressed(input::KeyCode::Escape))
		m_message_bus->send(core::CloseGameMessage{});
}

void itd::Application::render()
{
	graphics::Graphics::RenderState render_state;
	m_graphics->set_render_state(render_state);

	float clear_color[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	m_graphics->clear_color_attachment(0, clear_color);

	m_scene_manager->render(m_time_manager->render_alpha());

	m_window->swap_buffers();
}

void itd::Application::end_frame()
{
	if (m_worker_thread->failed())
		std::rethrow_exception(m_worker_thread->error());

	m_time_manager->end_frame();
}
