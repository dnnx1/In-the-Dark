#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include "engine/core/worker/worker_api.h"

namespace itd::core
{
	class WorkerThread
	{
	public:
		WorkerThread();
		~WorkerThread();

		WorkerThread(const WorkerThread&) = delete;
		WorkerThread(WorkerThread&&) = delete;

		WorkerThread& operator=(const WorkerThread&) = delete;
		WorkerThread& operator=(WorkerThread&&) = delete;

	public:
		static std::shared_ptr<WorkerThread> make_shared();

	public:
		void push(WorkerAPI::Task&& _task);
		void stop();

		bool failed() const;
		std::exception_ptr error() const;

	private:
		void loop();

	private:
		std::thread m_thread;
		std::atomic_bool m_stop{ false };
		std::mutex m_mtx;
		std::condition_variable m_cv;

		std::atomic_bool m_failed{ false };
		std::exception_ptr m_exception;

		std::queue<WorkerAPI::Task> m_queue;
	};
}