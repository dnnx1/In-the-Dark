#pragma once
#include <memory>
#include "in_the_dark/input/cursor/cursor_api.h"

namespace itd::input
{
	class Cursor : CursorAPI
	{
	public:
		Cursor();
		~Cursor();

		Cursor(const Cursor&) = delete;
		Cursor(Cursor&&) = delete;

		Cursor& operator=(const Cursor&) = delete;
		Cursor& operator=(Cursor&&) = delete;

	public:
		static std::unique_ptr<Cursor> make_unique();

	public:
		glm::vec2 position() const override;
		void set_position(glm::vec2 _position);

	private:
		glm::vec2 m_position{ 0.0f };
	};
}