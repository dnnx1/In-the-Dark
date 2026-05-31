#include "in_the_dark/time/clock/clock.h"

itd::time::Clock::Clock(bool _running, float _time_scale)
	: m_running(_running)
	, m_time_scale(_time_scale)
{
}

void itd::time::Clock::set_time_scale(float _scale)
{
	m_time_scale = _scale;
}

void itd::time::Clock::start()
{
	m_running = true;
	m_value = 0.0f;
}

void itd::time::Clock::stop()
{
	m_running = false;
	m_value = 0.0f;
}

void itd::time::Clock::pause()
{
	m_running = false;
}

void itd::time::Clock::resume()
{
	m_running = true;
}

float itd::time::Clock::value() const
{
	return m_value;
}

void itd::time::Clock::update(float _dt)
{
	if (!m_running) return;
	m_value += _dt * m_time_scale;
}
