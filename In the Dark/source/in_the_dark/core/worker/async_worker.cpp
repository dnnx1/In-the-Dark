#include "in_the_dark/engine_api.h"
#include "in_the_dark/core/worker/async_worker.h"

itd::core::AsyncWorker::AsyncWorker(std::shared_ptr<WorkerThread> _worker_thread)
	: m_worker_thread(std::move(_worker_thread))
{
	EngineAPI::instance().async_worker = this;
}

itd::core::AsyncWorker::~AsyncWorker()
{
	if (EngineAPI::instance().async_worker == this)
		EngineAPI::instance().async_worker = nullptr;
}

std::unique_ptr<itd::core::AsyncWorker> itd::core::AsyncWorker::make_unique(std::shared_ptr<WorkerThread> _worker_thread)
{
	return std::make_unique<AsyncWorker>(_worker_thread);
}

void itd::core::AsyncWorker::push(Task&& _task)
{
	m_worker_thread->push(std::move(_task));
}