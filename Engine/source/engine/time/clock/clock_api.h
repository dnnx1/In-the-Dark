#pragma once

namespace itd::time
{
	class ClockAPI
	{
	public:
		virtual ~ClockAPI() = default;

	public:
		virtual void set_time_scale(float _scale) = 0;

		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual float value() const = 0;
	};
}