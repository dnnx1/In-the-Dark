#pragma once
#include "engine/core/worker/worker_thread.h"

namespace itd::core
{
	class AsyncWorker : public WorkerAPI
	{
	public:
		AsyncWorker(std::shared_ptr<WorkerThread> _worker_thread);
		~AsyncWorker();

		AsyncWorker(const AsyncWorker&) = delete;
		AsyncWorker(AsyncWorker&&) = delete;

		AsyncWorker& operator=(const AsyncWorker&) = delete;
		AsyncWorker& operator=(AsyncWorker&&) = delete;

	public:
		static std::unique_ptr<AsyncWorker> make_unique(std::shared_ptr<WorkerThread> _worker_thread);

	public:
		void push(Task&& _task) override;

	private:
		std::shared_ptr<WorkerThread> m_worker_thread;
	};
}