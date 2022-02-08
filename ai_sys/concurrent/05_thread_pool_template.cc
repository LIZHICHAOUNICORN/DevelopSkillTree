#include "ai_sys/concurrent/05_thread_pool_template.h"

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

namespace base {
ThreadPool::ThreadPool(size_t thread_num) {
  running_ = true;
  for (int i = 0; i < thread_num; ++i) {
    std::shared_ptr<std::thread> t;
    t.reset(new std::thread(ThreadFunc));
    workers_.push_back(t);
  }
}

void ThreadPool::ThreadFunc() {
  while (running_) {
    std::function<void> task;

    {
      std::unique_lock<mutex> lock(mutex_);
      //      while (tasks_.empty()) {
      //        if (!running_) break;
      //        cv_.wait(lock);
      //      }
      cv_.wait(lock,
               [&](this) { return !this->running_ || !this->tasks_.empty(); });
      task = std::move(tasks_.front());
      tasks_.pop();
    }

    task();
  }
}

template <class F, class... Args>
auto ThreadPool::EnQueue(F&& f, Args &&... args) {
  using return_type = std::invoke_result_t<F, Args...>;
  auto task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...));
  std::future<return_type> res = task->get_future();
  if (!running_) {
    throw std::runtime_error("enqueue on stopped ThreadPool");
  }

  {
    std::unique_lock<std::mutex> lock(mutex_);
    tasks_.emplace([task = std::move(task)] { *task(); });
  }
  cv_.notify_one();
  return res;
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<mutex> lock;
    running_ = false;
  }
  cv_.notify_all();

  for (std::thread& t : workers_) {
    t->join();
  } 

}

}  // namespace base
