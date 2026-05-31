#pragma once
#include "in_the_dark/input/common/key_code.h"

namespace itd::input
{
	class KeyboardAPI
	{
	public:
		virtual ~KeyboardAPI() = default;

	public:
		virtual bool pressed(KeyCode _code) const = 0;
		virtual bool just_pressed(KeyCode _code) const = 0;
		virtual bool released(KeyCode _code) const = 0;
	};
}