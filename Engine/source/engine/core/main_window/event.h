#pragma once
#include <variant>
#include "external/glm/vec2.hpp"
#include "engine/input/common/action.h"
#include "engine/input/common/key_code.h"
#include "engine/input/common/modifier.h"
#include "engine/input/common/mouse_code.h"

namespace itd::core
{
	struct WindowSizeEvent { glm::ivec2 size{ 0 }; };
	struct WindowFocusEvent { bool focused{ false }; };
	struct WindowIconifyEvent { bool iconified{ false }; };
	struct WindowMaximizeEvent { bool maximized{ false }; };
	struct WindowContentScaleEvent { glm::vec2 scale{ 0.0f }; };
	struct WindowPosEvent { glm::ivec2 position{ 0 }; };
	struct WindowCloseEvent {};
	struct FramebufferSizeEvent { glm::ivec2 size{ 0 }; };
	struct CharEvent { unsigned int codepoint{ 0 }; };
	struct CursorPosEvent { glm::vec2 position{ 0.0f }; };
	struct CursorEnterEvent { bool entered{ false }; };
	struct ScrollEvent { glm::vec2 offset{ 0.0f }; };
	struct KeyEvent
	{
		input::KeyCode code{ input::KeyCode::Undefined };
		input::Action action{ input::Action::Undefined };
		input::Modifier mods{ input::Modifier::None };
	};
	struct MouseButtonEvent
	{
		input::MouseCode code{ input::MouseCode::Undefined };
		input::Action action{ input::Action::Undefined };
		input::Modifier mods{ input::Modifier::None };
	};

	using Event = std::variant<
		std::monostate,
		WindowSizeEvent,
		WindowFocusEvent,
		WindowIconifyEvent,
		WindowMaximizeEvent,
		WindowContentScaleEvent,
		WindowPosEvent,
		WindowCloseEvent,
		FramebufferSizeEvent,
		CharEvent,
		CursorPosEvent,
		CursorEnterEvent,
		ScrollEvent,
		KeyEvent,
		MouseButtonEvent
	>;

	//struct DropEvent { std::vector<std::string> paths; };
}