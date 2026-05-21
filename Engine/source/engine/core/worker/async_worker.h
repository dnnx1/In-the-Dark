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
	class AsyncWorker : public WorkerAPI
	{
	public:
		AsyncWorker();
		~AsyncWorker();

		AsyncWorker(const AsyncWorker&) = delete;
		AsyncWorker(AsyncWorker&&) = delete;

		AsyncWorker& operator=(const AsyncWorker&) = delete;
		AsyncWorker& operator=(AsyncWorker&&) = delete;

	public:
		static std::unique_ptr<AsyncWorker> make_unique();

	public:
		void push(Task&& _task) override;
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

		std::queue<Task> m_queue;

		std::atomic_bool m_failed{ false };
		std::exception_ptr m_exception;
	};
}