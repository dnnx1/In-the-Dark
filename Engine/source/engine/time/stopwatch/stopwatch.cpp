#include "engine/time/stopwatch/stopwatch.h"
#include "engine/utility/math.h"

itd::time::Stopwatch::Stopwatch(float _duration, bool _running, bool _loop, float _time_scale)
	: m_duration(_duration)
	, m_running(_running)
	, m_loop(_loop)
	, m_time_scale(_time_scale)
{
}

void itd::time::Stopwatch::set_time_scale(float _scale)
{
	m_time_scale = _scale;
}

void itd::time::Stopwatch::set_loop(bool _loop)
{
	m_loop = _loop;
}

void itd::time::Stopwatch::set_duration(float _duration)
{
	m_duration = _duration;
}

void itd::time::Stopwatch::set_callback(CallbackFunc&& _callback)
{
	m_callback = std::move(_callback);
}

void itd::time::Stopwatch::start()
{
	m_running = true;
	m_elapsed = 0.0f;
}

void itd::time::Stopwatch::stop()
{
	m_running = false;
	m_elapsed = 0.0f;
}

void itd::time::Stopwatch::pause()
{
	m_running = false;
}

void itd::time::Stopwatch::resume()
{
	m_running = true;
}

void itd::time::Stopwatch::invoke_callback()
{
	if (m_invoke_callback)
		m_callback();
}

float itd::time::Stopwatch::progress() const
{
	return m_progress;
}

bool itd::time::Stopwatch::finished() const
{
	return m_finished;
}

void itd::time::Stopwatch::update(float _dt)
{
	m_invoke_callback = false;
	m_finished = false;
	if (!m_running) return;

	if (m_loop) update_looped(_dt);
	else update_non_looped(_dt);
}

void itd::time::Stopwatch::update_looped(float _dt)
{
	m_elapsed += _dt * m_time_scale;
	calc_progress();
	while (m_elapsed >= m_duration)
	{
		m_elapsed -= m_duration;
		m_invoke_callback = true;
		m_finished = true;
	}
}

void itd::time::Stopwatch::update_non_looped(float _dt)
{
	m_elapsed += _dt * m_time_scale;
	calc_progress();
	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.0f;
		m_invoke_callback = true;
		m_finished = true;
		m_running = false;
	}
}

void itd::time::Stopwatch::calc_progress()
{
	m_progress = utility::epsilon_greater(m_duration, 0.0f) ? std::min((m_elapsed / m_duration), 1.0f) : 0.0f;
}
