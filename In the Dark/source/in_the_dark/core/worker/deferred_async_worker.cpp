#include "in_the_dark/engine_api.h"
#include "in_the_dark/core/worker/deferred_async_worker.h"

itd::core::DeferredAsyncWorker::DeferredAsyncWorker(std::shared_ptr<WorkerThread> _worker_thread)
	: m_worker_thread(std::move(_worker_thread))
{
	EngineAPI::instance().deferred_async_worker = this;
}

itd::core::DeferredAsyncWorker::~DeferredAsyncWorker()
{
	if (EngineAPI::instance().deferred_async_worker == this)
		EngineAPI::instance().deferred_async_worker = nullptr;
}

std::unique_ptr<itd::core::DeferredAsyncWorker> itd::core::DeferredAsyncWorker::make_unique(std::shared_ptr<WorkerThread> _worker_thread)
{
	return std::make_unique<DeferredAsyncWorker>(_worker_thread);
}

void itd::core::DeferredAsyncWorker::push(Task&& _task)
{
	std::unique_lock<std::mutex> ul(m_mtx);
	m_queue.push(std::move(_task));
}

void itd::core::DeferredAsyncWorker::dispatch()
{
	std::queue<Task> local_queue;
	{
		std::unique_lock<std::mutex> ul(m_mtx);
		local_queue.swap(m_queue);
	}

	while (!local_queue.empty())
	{
		m_worker_thread->push(std::move(local_queue.front()));
		local_queue.pop();
	}
}
