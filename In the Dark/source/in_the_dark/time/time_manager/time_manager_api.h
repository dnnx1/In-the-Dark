#pragma once
#include <memory>
#include "in_the_dark/time/clock/clock_api.h"
#include "in_the_dark/time/stopwatch/stopwatch_api.h"

namespace itd::time
{
	class TimeManagerAPI
	{
	public:
		virtual ~TimeManagerAPI() = default;

	public:
		virtual std::shared_ptr<ClockAPI> create_clock(bool _running = false, float _time_scale = 1.0f) = 0;
		virtual std::shared_ptr<StopwatchAPI> create_stopwatch(float _duration, bool _running = false, bool _loop = false, float _time_scale = 1.0f) = 0;
	};
}