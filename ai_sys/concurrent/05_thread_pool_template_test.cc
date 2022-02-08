#include "05_thread_pool_template.h"
#include <iostream>
#include <string>

std::string task(std::string str) { return "hello " + str; }

int main() {
  ThreadPool pool;
  pool.enqueue([] { std::cout << "hello\n"; });
  auto future =
      pool.enqueue([](std::string str) { return "hello " + str; }, "world");
  std::cout << future.get() << '\n';
}
