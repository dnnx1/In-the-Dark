#include "engine/core/main_window/main_window.h"

static itd::core::MainWindow* to_main_window(GLFWwindow* _glfw_window)
{
	return static_cast<itd::core::MainWindow*>(glfwGetWindowUserPointer(_glfw_window));
}

static itd::input::KeyCode to_key_code(int _native_code)
{
	using KeyCode = itd::input::KeyCode;
	switch (_native_code)
	{
	case GLFW_KEY_0:		return KeyCode::Num0;
	case GLFW_KEY_1:		return KeyCode::Num1;
	case GLFW_KEY_2:		return KeyCode::Num2;
	case GLFW_KEY_3:		return KeyCode::Num3;
	case GLFW_KEY_4:		return KeyCode::Num4;
	case GLFW_KEY_5:		return KeyCode::Num5;
	case GLFW_KEY_6:		return KeyCode::Num6;
	case GLFW_KEY_7:		return KeyCode::Num7;
	case GLFW_KEY_8:		return KeyCode::Num8;
	case GLFW_KEY_9:		return KeyCode::Num9;

	case GLFW_KEY_A:		return KeyCode::A;
	case GLFW_KEY_B:		return KeyCode::B;
	case GLFW_KEY_C:		return KeyCode::C;
	case GLFW_KEY_D:		return KeyCode::D;
	case GLFW_KEY_E:		return KeyCode::E;
	case GLFW_KEY_F:		return KeyCode::F;
	case GLFW_KEY_G:		return KeyCode::G;
	case GLFW_KEY_H:		return KeyCode::H;
	case GLFW_KEY_I:		return KeyCode::I;
	case GLFW_KEY_J:		return KeyCode::J;
	case GLFW_KEY_K:		return KeyCode::K;
	case GLFW_KEY_L:		return KeyCode::L;
	case GLFW_KEY_M:		return KeyCode::M;
	case GLFW_KEY_N:		return KeyCode::N;
	case GLFW_KEY_O:		return KeyCode::O;
	case GLFW_KEY_P:		return KeyCode::P;
	case GLFW_KEY_Q:		return KeyCode::Q;
	case GLFW_KEY_R:		return KeyCode::R;
	case GLFW_KEY_S:		return KeyCode::S;
	case GLFW_KEY_T:		return KeyCode::T;
	case GLFW_KEY_U:		return KeyCode::U;
	case GLFW_KEY_V:		return KeyCode::V;
	case GLFW_KEY_W:		return KeyCode::W;
	case GLFW_KEY_X:		return KeyCode::X;
	case GLFW_KEY_Y:		return KeyCode::Y;
	case GLFW_KEY_Z:		return KeyCode::Z;

	case GLFW_KEY_ESCAPE:	return KeyCode::Escape;
	case GLFW_KEY_SPACE:	return KeyCode::Space;
	case GLFW_KEY_LEFT:		return KeyCode::Left;
	case GLFW_KEY_RIGHT:	return KeyCode::Right;
	case GLFW_KEY_UP:		return KeyCode::Up;
	case GLFW_KEY_DOWN:		return KeyCode::Down;

	default:				return KeyCode::Undefined;
	}
}

static itd::input::MouseCode to_mouse_code(int _native_code)
{
	using MouseCode = itd::input::MouseCode;
	switch (_native_code)
	{
	case GLFW_MOUSE_BUTTON_LEFT:	return MouseCode::Left;
	case GLFW_MOUSE_BUTTON_MIDDLE:	return MouseCode::Middle;
	case GLFW_MOUSE_BUTTON_RIGHT:	return MouseCode::Right;

	default:						return MouseCode::Undefined;
	}
}

void itd::core::MainWindow::setup_callbacks()
{
	glfwSetWindowUserPointer(m_glfw_window.get(), this);

	glfwSetWindowSizeCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _width, int _height)
		{
			WindowSizeEvent evt;
			evt.size = glm::ivec2(_width, _height);
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetWindowFocusCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _focused)
		{
			WindowFocusEvent evt;
			evt.focused = _focused;
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetWindowIconifyCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _iconified)
		{
			WindowIconifyEvent evt;
			evt.iconified = _iconified;
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetWindowMaximizeCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _maximized)
		{
			WindowMaximizeEvent evt;
			evt.maximized = _maximized;
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetWindowContentScaleCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, float _scaleX, float _scaleY)
		{
			WindowContentScaleEvent evt;
			evt.scale = glm::vec2(_scaleX, _scaleY);
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetWindowPosCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _posX, int _posY)
		{
			WindowPosEvent evt;
			evt.position = glm::ivec2(_posX, _posY);
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetWindowCloseCallback(m_glfw_window.get(), [](GLFWwindow* _glfw)
		{
			WindowCloseEvent evt;
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetFramebufferSizeCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _width, int _height)
		{
			FramebufferSizeEvent evt;
			evt.size = glm::ivec2(_width, _height);
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetKeyCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _key, int /*_scancode*/, int _action, int /*_mods*/)
		{
			if (_action == GLFW_PRESS)
			{
				KeyEvent evt;
				evt.action = input::Action::Press;
				evt.code = to_key_code(_key);
				to_main_window(_glfw)->m_events.emplace(std::move(evt));
			}
			else if (_action == GLFW_RELEASE)
			{
				KeyEvent evt;
				evt.action = input::Action::Release;
				evt.code = to_key_code(_key);
				to_main_window(_glfw)->m_events.emplace(std::move(evt));
			}
		});

	glfwSetCharCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, unsigned int _codepoint)
		{
			CharEvent evt;
			evt.codepoint = _codepoint;
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetMouseButtonCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _key, int _action, int /*_mods*/)
		{
			if (_action == GLFW_PRESS)
			{
				MouseButtonEvent evt;
				evt.action = input::Action::Press;
				evt.code = to_mouse_code(_key);
				to_main_window(_glfw)->m_events.emplace(std::move(evt));
			}
			else if (_action == GLFW_RELEASE)
			{
				MouseButtonEvent evt;
				evt.action = input::Action::Release;
				evt.code = to_mouse_code(_key);
				to_main_window(_glfw)->m_events.emplace(std::move(evt));
			}
		});

	glfwSetCursorPosCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, double _x, double _y)
		{
			CursorPosEvent evt;
			evt.position = glm::vec2(_x, _y);
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetCursorEnterCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, int _entered)
		{
			CursorEnterEvent evt;
			evt.entered = _entered;
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});

	glfwSetScrollCallback(m_glfw_window.get(), [](GLFWwindow* _glfw, double _offsetX, double _offsetY)
		{
			ScrollEvent evt;
			evt.offset = glm::vec2(_offsetX, _offsetY);
			to_main_window(_glfw)->m_events.emplace(std::move(evt));
		});
}