#include "ai_sys/concurrent/05_thread_pool_template.h"

#include <iostream>

bool GetResult(const std::string& result) {
  std::cout << result << std::endl;
  return true;
}

int main(int argc, char* argv[]) {
  base::ThreadPool pool;
  auto f =
      pool.EnQueue([](std::string str) { return "hello " + str; }, "world");
  std::cout << f.get() << std::endl;

  return 0;
}
