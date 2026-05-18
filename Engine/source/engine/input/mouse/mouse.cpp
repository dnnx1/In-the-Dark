#include "engine/core/engine_api.h"
#include "engine/input/mouse/mouse.h"
#include "engine/input/frame_counter.h"

itd::input::Mouse::Mouse()
{
	core::EngineAPI::instance().mouse = this;
}

itd::input::Mouse::~Mouse()
{
	if (core::EngineAPI::instance().mouse == this)
		core::EngineAPI::instance().mouse = nullptr;
}

std::unique_ptr<itd::input::Mouse> itd::input::Mouse::make_unique()
{
	return std::make_unique<Mouse>();
}

bool itd::input::Mouse::clicked(MouseCode _code) const
{
	return m_data[utility::to_underlying(_code)].active;
}

bool itd::input::Mouse::just_clicked(MouseCode _code) const
{
	return m_data[utility::to_underlying(_code)].active && m_data[utility::to_underlying(_code)].frame == FrameCounter::value;
}

bool itd::input::Mouse::released(MouseCode _code) const
{
	return !m_data[utility::to_underlying(_code)].active && m_data[utility::to_underlying(_code)].frame == FrameCounter::value;
}

void itd::input::Mouse::set(MouseCode _code, Action _action)
{
	m_data[utility::to_underlying(_code)].active = (_action == Action::Press) ? true : false;
	m_data[utility::to_underlying(_code)].frame = FrameCounter::value;
}