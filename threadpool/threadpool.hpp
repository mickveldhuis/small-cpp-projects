#pragma once

#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>


/// Basic thread pool implementation.
class ThreadPool {
public:
  ThreadPool(std::size_t n_threads);
  ~ThreadPool();

  void push_task(std::function<void()> task);
  void stop();

  void wait_until_finished();

private:
  void worker();

  std::vector<std::thread> threads_;
  std::queue<std::function<void()>> tasks_;

  std::mutex mutex_;
  std::condition_variable mutex_condition_;

  std::condition_variable tasks_finished_condition_;

  bool stop_{false};

  std::size_t active_tasks_{0};
};