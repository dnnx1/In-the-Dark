#pragma once
#include <list>
#include <chrono>
#include "engine/time/time_manager/time_manager_api.h"
#include "engine/time/clock/clock.h"
#include "engine/time/stopwatch/stopwatch.h"

namespace itd::time
{
	class TimeManager : public TimeManagerAPI
	{
	private:
		using steady_clock = std::chrono::steady_clock;
		using nanoseconds = std::chrono::nanoseconds;

	public:
		TimeManager(float _dt_cap, float _fixed_dt, int _max_fixed_steps);
		~TimeManager();

		TimeManager(const TimeManager&) = delete;
		TimeManager(TimeManager&&) = delete;

		TimeManager& operator=(const TimeManager&) = delete;
		TimeManager& operator=(TimeManager&&) = delete;

	public:
		static std::unique_ptr<TimeManager> make_unique(float _dt_cap = 0.1f, float _fixed_dt = 1.0f / 50.0f, int _max_fixed_steps = 5);

	public:
		template <typename Func> void fixed_loop(Func&& _func)
		{
			while (m_accumulator >= m_fixed_delta_time)
			{
				m_accumulator -= m_fixed_delta_time;
				_func(m_fixed_delta_time);
			}
		}

	public:
		std::shared_ptr<ClockAPI> create_clock(bool _running = false, float _time_scale = 1.0f) override;
		std::shared_ptr<StopwatchAPI> create_stopwatch(float _duration, bool _running = false, bool _loop = false, float _time_scale = 1.0f) override;

		void update();
		void prepare_to_game_loop();

		void set_framerate(int _fps);
		void begin_frame();
		void end_frame();

		float delta_time() const;
		float fixed_delta_time() const;
		float render_alpha() const;

	private:
		nanoseconds m_framerate{ 0 };
		steady_clock::time_point m_frame_start_tp;

		float m_delta_time{ 0.0f };
		float m_delta_time_cap{ 0.0f };

		float m_fixed_delta_time{ 0.0f };
		float m_accumulator{ 0.0f };
		float m_max_accumulator{ 0.0f };

		steady_clock::time_point m_prev_tp;
		steady_clock::time_point m_curr_tp;

		std::list<std::weak_ptr<Clock>> m_clock_list;
		std::list<std::weak_ptr<Stopwatch>> m_stopwatch_list;
	};
}