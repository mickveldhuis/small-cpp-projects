#include "threadpool.hpp"

#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

ThreadPool::ThreadPool(std::size_t n_threads) {
  const std::size_t max_n_threads = std::thread::hardware_concurrency();
	
	std::clog << "Maximum number of available threads = " << max_n_threads << std::endl;

	if (n_threads > max_n_threads) {
    throw std::runtime_error("Requested more threads (" +
                             std::to_string(n_threads) + ") than available (" +
                             std::to_string(max_n_threads) + ")");
  }

	for (int t = 0; t < n_threads; ++t) {
		threads_.emplace_back([this] () { worker(); });
	}
}

ThreadPool::~ThreadPool() {
	stop();
}

void ThreadPool::worker() {
	while(true) {
		std::function<void()> task;
		
		std::unique_lock<std::mutex> lock(mutex_);
		mutex_condition_.wait(lock, [this] () { return !tasks_.empty() || stop_; });

		if (stop_) {
			break;
		}

		task = std::move(tasks_.front());
		tasks_.pop();

		++active_tasks_;
		
		lock.unlock();

		task();

		lock.lock();
		--active_tasks_;

		// TODO: only notify when the caller calls wait_until_finished().
		tasks_finished_condition_.notify_all();
		lock.unlock();
	}
}

void ThreadPool::push_task(std::function<void()> task) {
	std::unique_lock<std::mutex> lock(mutex_);
	tasks_.push(std::move(task));
	lock.unlock();

	mutex_condition_.notify_one();
}

void ThreadPool::stop() {
	std::unique_lock<std::mutex> lock(mutex_);
	stop_ = true;
	lock.unlock();

	mutex_condition_.notify_all();
	for (std::thread& thread : threads_) {
		thread.join();
	}
	threads_.clear();

	// TODO: figure out how to reuse the thread pool...
	stop_ = false;
}

void ThreadPool::wait_until_finished() {
  std::unique_lock<std::mutex> lock(mutex_);
  
	tasks_finished_condition_.wait(lock, [this] () { return tasks_.empty() && active_tasks_ == 0; });
	
	lock.unlock();
}