#pragma once
#include <functional>

namespace itd::time
{
	class StopwatchAPI
	{
	public:
		using CallbackFunc = std::function<void()>;

	public:
		virtual ~StopwatchAPI() = default;

	public:
		virtual void set_time_scale(float _scale) = 0;
		virtual void set_loop(bool _loop) = 0;
		virtual void set_duration(float _duration) = 0;
		virtual void set_callback(CallbackFunc&& _callback) = 0;

		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void invoke_callback() = 0;
		virtual float progress() const = 0;
		virtual bool finished() const = 0;
	};
}