#include <iostream>

#include "threadpool.hpp"

int main() {
  using namespace std::chrono_literals;

  const int n_tasks = 16;

  std::vector<int> squares(n_tasks);

  ThreadPool pool(4);

  for (int i = 0; i < n_tasks; ++i) {
    pool.push_task([i, &squares] () {
      squares[i] = i * i;
      std::this_thread::sleep_for(100ms);
    });
  }

  pool.wait_until_finished();

  std::cout << "Got some results: ";
  for (int s : squares) {
    std::cout << s << " ";
  }
  std::cout << std::endl;
}
