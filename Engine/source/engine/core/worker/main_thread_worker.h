#pragma once
#include <memory>
#include <queue>
#include <mutex>
#include "engine/core/worker/worker_api.h"

namespace itd::core
{
	class MainThreadWorker : public WorkerAPI
	{
	public:
		MainThreadWorker();
		~MainThreadWorker();

		MainThreadWorker(const MainThreadWorker&) = delete;
		MainThreadWorker(MainThreadWorker&&) = delete;

		MainThreadWorker& operator=(const MainThreadWorker&) = delete;
		MainThreadWorker& operator=(MainThreadWorker&&) = delete;

	public:
		static std::unique_ptr<MainThreadWorker> make_unique();

	public:
		void push(Task&& _task) override;
		void execute();

	private:
		std::queue<Task> m_queue;
		std::mutex m_mtx;
	};
}