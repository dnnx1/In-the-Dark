#include "engine/engine_api.h"
#include "engine/error.h"
#include "engine/core/worker/main_thread_worker.h"

itd::core::MainThreadWorker::MainThreadWorker()
{
	EngineAPI::instance().main_thread_worker = this;
}

itd::core::MainThreadWorker::~MainThreadWorker()
{
	if (EngineAPI::instance().main_thread_worker == this)
		EngineAPI::instance().main_thread_worker = nullptr;
}

std::unique_ptr<itd::core::MainThreadWorker> itd::core::MainThreadWorker::make_unique()
{
	return std::make_unique<MainThreadWorker>();
}

void itd::core::MainThreadWorker::push(Task&& _task)
{
	std::unique_lock<std::mutex> ul(m_mtx);
	m_queue.push(std::move(_task));
}

void itd::core::MainThreadWorker::execute()
{
	std::queue<Task> local_queue;
	{
		std::unique_lock<std::mutex> ul(m_mtx);
		local_queue.swap(m_queue);
	}

	while (!local_queue.empty())
	{
		local_queue.front()();
		local_queue.pop();
	}
}
