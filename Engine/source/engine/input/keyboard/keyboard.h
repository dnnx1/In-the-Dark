#pragma once
#include <array>
#include <memory>
#include "engine/input/keyboard/keyboard_api.h"
#include "engine/input/common/action.h"
#include "engine/utility/enum.h"

namespace itd::input
{
	class Keyboard : public KeyboardAPI
	{
	private:
		struct KeyData
		{
			bool active{ false };
			unsigned int frame{ 0 };
		};

	public:
		Keyboard();
		~Keyboard();

		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;

		Keyboard& operator= (const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;

	public:
		static std::unique_ptr<Keyboard> make_unique();

	public:
		bool pressed(KeyCode _code) const override;
		bool just_pressed(KeyCode _code) const override;
		bool released(KeyCode _code) const override;
		void set(KeyCode _code, Action _action);

	private:
		std::array<KeyData, utility::to_underlying(KeyCode::__count)> m_data;
	};
}