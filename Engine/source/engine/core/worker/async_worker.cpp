#include "engine/engine_api.h"
#include "engine/error.h"
#include "engine/core/worker/main_thread_worker.h"
#include "async_worker.h"

itd::core::AsyncWorker::AsyncWorker()
	: m_thread(&AsyncWorker::loop, this)
{
	EngineAPI::instance().async_worker = this;
}

itd::core::AsyncWorker::~AsyncWorker()
{
	stop();

	if (EngineAPI::instance().async_worker == this)
		EngineAPI::instance().async_worker = nullptr;
}

std::unique_ptr<itd::core::AsyncWorker> itd::core::AsyncWorker::make_unique()
{
	return std::make_unique<AsyncWorker>();
}

void itd::core::AsyncWorker::push(Task&& _task)
{
	{
		std::unique_lock<std::mutex> ul(m_mtx);
		m_queue.push(std::move(_task));
	}
	m_cv.notify_one();
}

void itd::core::AsyncWorker::stop()
{
	if (m_thread.joinable())
	{
		m_stop.store(true);
		m_cv.notify_one();
		m_thread.join();
	}
}

bool itd::core::AsyncWorker::failed() const
{
	return m_failed.load();;
}

std::exception_ptr itd::core::AsyncWorker::error() const
{
	return m_exception;
}

void itd::core::AsyncWorker::loop()
{
	try
	{
		auto predicate = [this]() {return !m_queue.empty() || m_stop.load(); };

		while (true)
		{
			Task task;
			{
				std::unique_lock<std::mutex> ul(m_mtx);
				m_cv.wait(ul, predicate);
				if (m_stop.load() && m_queue.empty()) break;

				task = std::move(m_queue.front());
				m_queue.pop();
			}
			task();
		}
	}
	catch (...)
	{
		std::unique_lock<std::mutex> ul(m_mtx);
		m_exception = std::current_exception();
		m_queue = {};
		m_failed.store(true);
	}
}
