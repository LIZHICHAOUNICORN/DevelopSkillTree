#include <iostream>
#include <string>
#include "05_simple_thread_pool.h"

void task(std::string str) { std::cout << "hello " + str << std::endl; }

int main(int args, char* argv[]) {
  util::SimplePool pool;
  pool.EnQueue([] { std::cout << "hello\n"; });
  // auto future = pool.enqueue([](std::string str) { return "hello " + str; },
  // "world");
  std::string msg(" world!");
  std::function<void()> f = std::bind(task, msg);
  pool.EnQueue(f);
}
