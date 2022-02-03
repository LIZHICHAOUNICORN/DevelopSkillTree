#include <chrono>

#include "ai_sys/concurrent/ThreadPool.h"

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

int main() {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  TaskPool thread_pool(5);

  Task* task = nullptr;
  for (int i = 0; i < 10; ++i) {
    task = new Task();
    thread_pool.addTask(task);
  }

  std::this_thread::sleep_for(std::chrono::seconds(5));

  thread_pool.stop();

  return 0;
}
