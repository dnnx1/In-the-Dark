#pragma once
#include "in_the_dark/time/stopwatch/stopwatch_api.h"

namespace itd::time
{
	class Stopwatch : public StopwatchAPI
	{
	public:
		Stopwatch(float _duration, bool _running, bool _loop, float _time_scale);
		~Stopwatch() = default;

		Stopwatch(const Stopwatch&) = delete;
		Stopwatch(Stopwatch&&) = default;

		Stopwatch& operator=(const Stopwatch&) = delete;
		Stopwatch& operator=(Stopwatch&&) = default;

	public:
		void set_time_scale(float _scale) override;
		void set_loop(bool _loop) override;
		void set_duration(float _duration) override;
		void set_callback(CallbackFunc&& _callback) override;

		void start() override;
		void stop() override;
		void pause() override;
		void resume() override;

		void invoke_callback() override;
		float progress() const override;
		bool finished() const override;

		void update(float _dt);

	private:
		void update_looped(float _dt);
		void update_non_looped(float _dt);
		void calc_progress();

	private:
		float m_time_scale{ 1.0f };
		float m_duration{ 0.0f };
		float m_elapsed{ 0.0f };
		float m_progress{ 0.0f };

		bool m_loop{ false };
		bool m_running{ false };
		bool m_finished{ false };
		bool m_invoke_callback{ false };

		CallbackFunc m_callback{ []() {} };
	};
}