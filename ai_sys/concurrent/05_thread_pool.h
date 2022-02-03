#ifndef CONCURRENT_THREAD_POOL_H_
#define CONCURRENT_THREAD_POOL_H_

#include <memory>
#include <mutex>
#include <thread>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

namespace base {

class Task {
 public:
  Task() = default;
  virtual ~Task() { LOG(INFO) << "task clean"; }

  virtual void Do() { LOG(INFO) << "task do"; }
};

class ThreadPool final {
 public:
  explicit ThreadPool(int thread_num);
  ThreadPool(const TaskPool& rhs) = delete;
  ThreadPool& operator=(const TaskPool& rhs) = delete;
  ~ThreadPool();

  void Stop();
  void AddTask(Task* task);
  void RemoveAllTasks();

 private:
  void Init(int thread_num);
  void thread_func();

  std::list<std::shared_ptr<Task>> task_list_;
  std::vector<std::threads> threads_;
  std::mutex mutex_;
  std::condition_variable cv_;
};

}  // namespace base

#endif  //   CONCURRENT_THREAD_POOL_H_
