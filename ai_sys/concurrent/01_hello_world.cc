#include <iostream>
#include <thread>

void hello() { std::cout << "Hello World from new thread." << std::endl; }

int main() {
  std::thread t(hello);
  t.join();

  return 0;
}
