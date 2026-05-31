#pragma once
#include <array>
#include <memory>
#include "in_the_dark/input/mouse/mouse_api.h"
#include "in_the_dark/input/common/action.h"
#include "in_the_dark/utility/enum.h"

namespace itd::input
{
	class Mouse : public MouseAPI
	{
	private:
		struct KeyData
		{
			bool active{ false };
			unsigned int frame{ 0 };
		};

	public:
		Mouse();
		~Mouse();

		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;

		Mouse& operator= (const Mouse&) = delete;
		Mouse& operator=(Mouse&&) = delete;

	public:
		static std::unique_ptr<Mouse> make_unique();

	public:
		bool clicked(MouseCode _code) const override;
		bool just_clicked(MouseCode _code) const override;
		bool released(MouseCode _code) const override;
		void set(MouseCode _code, Action _action);

	private:
		std::array<KeyData, utility::to_underlying(MouseCode::__count)> m_data;
	};
}