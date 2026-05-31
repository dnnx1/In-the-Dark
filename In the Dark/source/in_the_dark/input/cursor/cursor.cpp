#include "in_the_dark/engine_api.h"
#include "in_the_dark/input/cursor/cursor.h"

itd::input::Cursor::Cursor()
{
	EngineAPI::instance().cursor = this;
}

itd::input::Cursor::~Cursor()
{
	if (EngineAPI::instance().cursor == this)
		EngineAPI::instance().cursor = nullptr;
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
