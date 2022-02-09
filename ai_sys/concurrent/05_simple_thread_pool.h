#include <functional>
#include <thread>
#include <vector>
#include "05_task_queue.h"

namespace util {
class SimplePool {
 public:
  using task_t = std::function<void()>;

  SimplePool(size_t thread_num = std::thread::hardware_concurrency()) {
    for (int i = 0; i < thread_num; ++i) {
      std::shared_ptr<std::thread> worker(new std::thread(std::bind(&SimplePool::ThreadFunc, this)));
      workers_.push_back(worker);
    }
  }
  void EnQueue(task_t t) { tasks_.Push(t); }

  ~SimplePool() {
    tasks_.Stop();
    for (auto& t : workers_) {
      t->join();
    }
  }
  void ThreadFunc() {
    while (true) {
      task_t t;
      if (tasks_.Pop(t)) {
        t();
      } else {
        break;
      }
    };
  }

 private:
  std::vector<std::shared_ptr<std::thread>> workers_;
  util::Queue<task_t> tasks_;
};

}  // namespace util
