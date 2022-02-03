#include <chrono>

#include "ai_sys/concurrent/05_thread_pool.h"

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  base::ThreadPool thread_pool(5);

  base::Task* task = nullptr;
  for (int i = 0; i < 10; ++i) {
    task = new base::Task();
    thread_pool.AddTask(task);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  thread_pool.Stop();

  return 0;
}
