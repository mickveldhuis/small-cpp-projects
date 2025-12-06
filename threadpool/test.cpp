#include <gtest/gtest.h>

#include "threadpool.hpp"

TEST(ThreadPoolTest, test_thread_pool) {
  using namespace std::chrono_literals;

  const int n_tasks = 16;

  std::vector<int> squares(n_tasks);

  ThreadPool pool(4);

  for (int i = 0; i < n_tasks; ++i) {
    pool.PushTask([i, &squares] () {
      squares[i] = i * i;
      std::this_thread::sleep_for(100ms);
    });
  }

  pool.WaitUntilFinished();

  for (int i = 0; i < n_tasks; ++i) {
    EXPECT_EQ(squares[i], i * i);
  }
}
