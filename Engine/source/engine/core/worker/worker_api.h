#pragma once
#include <functional>

namespace itd::core
{
	class WorkerAPI
	{
	public:
		using Task = std::function<void()>;

	public:
		virtual ~WorkerAPI() = default;

	public:
		virtual void push(Task&& _task) = 0;
	};
}