#ifndef CONCURRENT_THREAD_POOL_TEMPLATE_H_
#define CONCURRENT_THREAD_POOL_TEMPLATE_H_

#include <memory>
#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

namespace base {

class ThreadPool final {
 public:
  explicit ThreadPool(size_t thread_num = std::thread::hardware_concurrency());
  ~ThreadPool();

  template <class F, class... Args>
  auto EnQueue(F&& f, Args...&& args);

 private:
  void ThreadFunc();

  std::vector<std::shared_ptr<std::thread>> workers_;
  std::queue<std::function<void>> tasks_; 
  std::mutex mutex_;
  std::condition_variable cv_;

  bool running_ = false;

};

}  // namespace base

#endif  //   CONCURRENT_THREAD_POOL_H_
