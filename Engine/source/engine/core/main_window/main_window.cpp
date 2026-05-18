#include "engine/core/error.h"
#include "engine/core/engine_api.h"
#include "engine/core/main_window/main_window.h"

itd::core::MainWindow::MainWindow(const CreationInfo& _info)
{
	if (glfwInit() != GLFW_TRUE)
		throw Error("MainWindow", "GLFW initialization failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindowPtr glfw_window(glfwCreateWindow(_info.width, _info.height, _info.title, nullptr, nullptr), glfwDestroyWindow);
	if (!glfw_window)
		throw Error("MainWindow", "GLFWwindow creation failed");

	m_glfw_window.swap(glfw_window);
	glfwMakeContextCurrent(m_glfw_window.get());

	m_mode = Mode::Windowed;
	m_windowed_position = position();
	m_windowed_size = size();

	setup_callbacks();
	EngineAPI::instance().window = this;
}

itd::core::MainWindow::~MainWindow()
{
	glfwTerminate();
	if (EngineAPI::instance().window == this)
		EngineAPI::instance().window = nullptr;
}

std::unique_ptr<itd::core::MainWindow> itd::core::MainWindow::make_unique(int _width, int _height, const char* _title)
{
	return std::make_unique<MainWindow>(CreationInfo{ _width, _height, _title });
}

void itd::core::MainWindow::set_position(glm::ivec2 _pos)
{
	if (m_mode != Mode::Windowed || maximized() || iconified()) return;
	glfwSetWindowPos(m_glfw_window.get(), _pos.x, _pos.y);
	m_windowed_position = _pos;
}

void itd::core::MainWindow::set_position(int _x, int _y)
{
	set_position({ _x, _y });
}

glm::ivec2 itd::core::MainWindow::position() const
{
	glm::ivec2 res{};
	glfwGetWindowPos(m_glfw_window.get(), &res.x, &res.y);
	return res;
}

void itd::core::MainWindow::set_size(glm::ivec2 _size)
{
	if (m_mode != Mode::Windowed || maximized() || iconified()) return;
	glfwSetWindowSize(m_glfw_window.get(), _size.x, _size.y);
	m_windowed_size = _size;
}

void itd::core::MainWindow::set_size(int _width, int _height)
{
	set_size({ _width, _height });
}

glm::ivec2 itd::core::MainWindow::size() const
{
	glm::ivec2 res{};
	glfwGetWindowSize(m_glfw_window.get(), &res.x, &res.y);
	return res;
}

glm::ivec2 itd::core::MainWindow::framebuffer_size() const
{
	glm::ivec2 res{};
	glfwGetFramebufferSize(m_glfw_window.get(), &res.x, &res.y);
	return res;
}

bool itd::core::MainWindow::iconified() const
{
	return glfwGetWindowAttrib(m_glfw_window.get(), GLFW_ICONIFIED);
}

bool itd::core::MainWindow::maximized() const
{
	return glfwGetWindowAttrib(m_glfw_window.get(), GLFW_MAXIMIZED);
}

bool itd::core::MainWindow::focused() const
{
	return glfwGetWindowAttrib(m_glfw_window.get(), GLFW_FOCUSED);
}

void itd::core::MainWindow::set_mode(Mode _mode)
{
	if (m_mode == _mode) return;
	m_mode = _mode;
	GLFWmonitor* monitor = nullptr;
	glm::ivec2 new_position{ 0 };
	glm::ivec2 new_size{ 0 };
	int refresh_rate = GLFW_DONT_CARE;

	switch (m_mode)
	{
	case Mode::Windowed:
	{
		new_position = m_windowed_position;
		new_size = m_windowed_size;

		glfwSetWindowAttrib(m_glfw_window.get(), GLFW_DECORATED, GLFW_TRUE);
	} break;

	case Mode::Borderless:
	{
		const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		new_size.x = vidmode->width;
		new_size.y = vidmode->height;

		glfwSetWindowAttrib(m_glfw_window.get(), GLFW_DECORATED, GLFW_FALSE);
	} break;

	case Mode::Fullscreen:
	{
		monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		new_size.x = vidmode->width;
		new_size.y = vidmode->height;
		refresh_rate = vidmode->refreshRate;

		glfwSetWindowAttrib(m_glfw_window.get(), GLFW_DECORATED, GLFW_FALSE);
	} break;

	default:
		break;
	}

	glfwSetWindowMonitor(m_glfw_window.get(), monitor, new_position.x, new_position.y, new_size.x, new_size.y, refresh_rate);
}

itd::core::MainWindow::Mode itd::core::MainWindow::mode() const
{
	return m_mode;
}

void itd::core::MainWindow::vsync(bool _enable)
{
	glfwSwapInterval(_enable ? 1 : 0);
}

void itd::core::MainWindow::swap_buffers()
{
	glfwSwapBuffers(m_glfw_window.get());
}
