#include "engine/core/engine_api.h"
#include "engine/input/keyboard/keyboard.h"
#include "engine/input/frame_counter.h"

itd::input::Keyboard::Keyboard()
{
	core::EngineAPI::instance().keyboard = this;
}

itd::input::Keyboard::~Keyboard()
{
	if (core::EngineAPI::instance().keyboard == this)
		core::EngineAPI::instance().keyboard = nullptr;
}

std::unique_ptr<itd::input::Keyboard> itd::input::Keyboard::make_unique()
{
	return std::make_unique<Keyboard>();
}

bool itd::input::Keyboard::pressed(KeyCode _code)
{
	return m_data[utility::to_underlying(_code)].active;
}

bool itd::input::Keyboard::just_pressed(KeyCode _code)
{
	return m_data[utility::to_underlying(_code)].active && m_data[utility::to_underlying(_code)].frame == FrameCounter::value;
}

bool itd::input::Keyboard::released(KeyCode _code)
{
	return !m_data[utility::to_underlying(_code)].active && m_data[utility::to_underlying(_code)].frame == FrameCounter::value;
}

void itd::input::Keyboard::set(KeyCode _code, Action _action)
{
	if (_action == Action::Undefined) return;
	m_data[utility::to_underlying(_code)].active = (_action == Action::Press) ? true : false;
	m_data[utility::to_underlying(_code)].frame = FrameCounter::value;
}