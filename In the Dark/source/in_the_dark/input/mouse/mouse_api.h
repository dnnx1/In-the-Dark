#pragma once
#include "in_the_dark/input/common/mouse_code.h"

namespace itd::input
{
	class MouseAPI
	{
	public:
		virtual ~MouseAPI() = default;

	public:
		virtual bool clicked(MouseCode _code) const = 0;
		virtual bool just_clicked(MouseCode _code) const = 0;
		virtual bool released(MouseCode _code) const = 0;
	};
}