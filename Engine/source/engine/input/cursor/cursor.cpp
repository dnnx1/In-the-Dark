#include "engine/core/engine_api.h"
#include "engine/input/cursor/cursor.h"

itd::input::Cursor::Cursor()
{
	core::EngineAPI::instance().cursor = this;
}

itd::input::Cursor::~Cursor()
{
	if (core::EngineAPI::instance().cursor == this)
		core::EngineAPI::instance().cursor = nullptr;
}

std::unique_ptr<itd::input::Cursor> itd::input::Cursor::make_unique()
{
	return std::make_unique<Cursor>();
}

glm::vec2 itd::input::Cursor::position() const
{
	return m_position;
}

void itd::input::Cursor::set_position(glm::vec2 _position)
{
	m_position = _position;
}
