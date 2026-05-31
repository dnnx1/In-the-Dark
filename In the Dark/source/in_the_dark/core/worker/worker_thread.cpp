#include "in_the_dark/core/worker/worker_thread.h"

itd::core::WorkerThread::WorkerThread()
	: m_thread(&WorkerThread::loop, this)
{
}

itd::core::WorkerThread::~WorkerThread()
{
	stop();
}

std::shared_ptr<itd::core::WorkerThread> itd::core::WorkerThread::make_shared()
{
	return std::make_shared<WorkerThread>();
}

void itd::core::WorkerThread::push(WorkerAPI::Task&& _task)
{
	if (m_stop.load() || m_failed.load()) return;

	{
		std::unique_lock<std::mutex> ul(m_mtx);
		m_queue.push(std::move(_task));
	}
	m_cv.notify_one();
}

void itd::core::WorkerThread::stop()
{
	if (m_thread.joinable())
	{
		m_stop.store(true);
		m_cv.notify_one();
		m_thread.join();
	}
}

bool itd::core::WorkerThread::failed() const
{
	return m_failed.load();
}

std::exception_ptr itd::core::WorkerThread::error() const
{
	return m_exception;
}

void itd::core::WorkerThread::loop()
{
	try
	{
		auto predicate = [this]() { return !m_queue.empty() || m_stop.load(); };

		while (true)
		{
			WorkerAPI::Task task;
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
		m_stop.store(true);
	}
}
