#pragma once
#include "in_the_dark/time/clock/clock_api.h"

namespace itd::time
{
	class Clock : public ClockAPI
	{
	public:
		Clock(bool _running, float _time_scale);
		~Clock() = default;

		Clock(const Clock&) = delete;
		Clock(Clock&&) = default;

		Clock& operator=(const Clock&) = delete;
		Clock& operator=(Clock&&) = default;

	public:
		void set_time_scale(float _scale) override;

		void start() override;
		void stop() override;
		void pause() override;
		void resume() override;

		float value() const override;

		void update(float _dt);

	private:
		float m_time_scale{ 1.0f };
		float m_value{ 0.0f };
		bool m_running{ false };
	};
}