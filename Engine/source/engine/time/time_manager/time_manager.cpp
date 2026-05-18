#define NOMINMAX
#include <thread>
#include <Windows.h>
#include "engine/engine_api.h"
#include "engine/time/time_manager/time_manager.h"
#include "engine/utility/math.h"

itd::time::TimeManager::TimeManager(float _dt_cap, float _fixed_dt, int _max_fixed_steps)
	: m_delta_time_cap(_dt_cap)
	, m_fixed_delta_time(_fixed_dt)
{
	m_max_accumulator = static_cast<float>(_max_fixed_steps) * m_fixed_delta_time;
	timeBeginPeriod(1);

	EngineAPI::instance().time_manager = this;
}

itd::time::TimeManager::~TimeManager()
{
	timeEndPeriod(1);

	if (EngineAPI::instance().time_manager == this)
		EngineAPI::instance().time_manager = nullptr;
}

std::unique_ptr<itd::time::TimeManager> itd::time::TimeManager::make_unique(float _dt_cap, float _fixed_dt, int _max_fixed_steps)
{
	return std::make_unique<TimeManager>(_dt_cap, _fixed_dt, _max_fixed_steps);
}

std::shared_ptr<itd::time::ClockAPI> itd::time::TimeManager::create_clock(bool _running, float _time_scale)
{
	auto clock = std::make_shared<Clock>(_running, _time_scale);
	m_clock_list.push_back(clock);
	return clock;
}

std::shared_ptr<itd::time::StopwatchAPI> itd::time::TimeManager::create_stopwatch(float _duration, bool _running, bool _loop, float _time_scale)
{
	auto stopwatch = std::make_shared<Stopwatch>(_duration, _running, _loop, _time_scale);
	m_stopwatch_list.push_back(stopwatch);
	return stopwatch;
}

void itd::time::TimeManager::update()
{
	m_curr_tp = steady_clock::now();
	float raw_delta_time = std::chrono::duration<float>(m_curr_tp - m_prev_tp).count();
	m_prev_tp = m_curr_tp;

	m_delta_time = std::min(raw_delta_time, m_delta_time_cap);

	m_accumulator += m_delta_time;
	m_accumulator = std::min(m_accumulator, m_max_accumulator);

	for (auto it = m_clock_list.begin(); it != m_clock_list.end();)
	{
		if (auto clock = it->lock()) { clock->update(m_delta_time); it++; }
		else { it = m_clock_list.erase(it); }
	}

	for (auto it = m_stopwatch_list.begin(); it != m_stopwatch_list.end();)
	{
		if (auto stopwatch = it->lock()) { stopwatch->update(m_delta_time); it++; }
		else { it = m_stopwatch_list.erase(it); }
	}
}

void itd::time::TimeManager::prepare_to_game_loop()
{
	auto now = steady_clock::now();
	m_prev_tp = now;
	m_curr_tp = now;
}

void itd::time::TimeManager::set_framerate(int _fps)
{
	_fps = std::max(_fps, 0);
	if (!_fps) m_framerate = nanoseconds(0);
	else m_framerate = nanoseconds(1'000'000'000ull / uint64_t(_fps));
}

void itd::time::TimeManager::begin_frame()
{
	m_frame_start_tp = steady_clock::now();
}

void itd::time::TimeManager::end_frame()
{
	if (!m_framerate.count()) return;

	while (true)
	{
		auto now = steady_clock::now();

		nanoseconds elapsed = std::chrono::duration_cast<nanoseconds>(now - m_frame_start_tp);
		if (elapsed >= m_framerate) break;

		nanoseconds remaining = m_framerate - elapsed;
		if (remaining > std::chrono::milliseconds(2))
		{
			std::this_thread::sleep_for(remaining - std::chrono::milliseconds(2));
		}
		else
		{
			_mm_pause();
		}
	}
}

float itd::time::TimeManager::delta_time() const
{
	return m_delta_time;
}

float itd::time::TimeManager::fixed_delta_time() const
{
	return m_fixed_delta_time;
}

float itd::time::TimeManager::render_alpha() const
{
	return utility::epsilon_greater(m_fixed_delta_time, 0.0f) ? std::min(m_accumulator / m_fixed_delta_time, 1.0f) : 0.0f;
}
