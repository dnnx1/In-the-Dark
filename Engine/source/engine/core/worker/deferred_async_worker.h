#pragma once
#include "engine/core/worker/worker_thread.h"

namespace itd::core
{
	class DeferredAsyncWorker : public WorkerAPI
	{
	public:
		DeferredAsyncWorker(std::shared_ptr<WorkerThread> _worker_thread);
		~DeferredAsyncWorker();

		DeferredAsyncWorker(const DeferredAsyncWorker&) = delete;
		DeferredAsyncWorker(DeferredAsyncWorker&&) = delete;

		DeferredAsyncWorker& operator=(const DeferredAsyncWorker&) = delete;
		DeferredAsyncWorker& operator=(DeferredAsyncWorker&&) = delete;

	public:
		static std::unique_ptr<DeferredAsyncWorker> make_unique(std::shared_ptr<WorkerThread> _worker_thread);

	public:
		void push(Task&& _task) override;
		void dispatch();

	private:
		std::shared_ptr<WorkerThread> m_worker_thread;

		std::queue<Task> m_queue;
		std::mutex m_mtx;
	};
}