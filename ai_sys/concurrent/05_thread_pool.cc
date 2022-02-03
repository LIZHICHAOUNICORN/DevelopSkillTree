#include "ai_sys/concurrent/thread_pool.h"

#include <memory>
#include <mutex>
#include <thread>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

namespace base {

ThreadPool::ThreadPool(int thread_num) : running_(false) { init(thread_num); }

ThreadPool::~ThreadPool() {
  if (running_) {
    running_ = false;
  }
  Stop();
  RemoveAllTasks();
}

void ThreadPool::Stop() {
  running_ = false;

  for (auto& iter : threads_) {
    if (iter->joinable()) iter->join();
  }
}

void ThreadPool::AddTask(Task* task) {
  std::shared_ptr<Task> task_ptr;
  task_ptr.reset(task);

  {
    std::lock_guard<std::mutex> guard(mutex_);
    task_list.push_back(task_ptr);
    LOG(INFO) << "add a Task." << task_ptr;
  }

  cv_.notify_one();
}

void ThreadPool::thread_func() {
  std::shared_ptr<Task> task;
  while (true) {
    std::unique_lock<std::mutex> guard(mutex_);
    while (task_list_.empty()) {
      if (!running_) break;

      //如果获得了互斥锁，但是条件不合适的话，pthread_cond_wait会释放锁，不往下执行。
      //当发生变化后，条件合适，pthread_cond_wait将直接获得锁。
      cv_.wait(guard);
    }

    if (!running_) break;

    task = task_list_.front();
    task_list_.pop_front();

    if (task == nullptr) continue;

    task->Do();
    task.reset();
  }

  LOG(INFO) << "exit thread, threadID: " << std::this_thread::get_id();
}

void ThreadPool::Init(int thread_num) {
  if (thread_num <= 0) thread_num = 5;

  running_ = true;

  for (int i = 0; i < thread_num; ++i) {
    std::shared_ptr<std::thread> thread;
    thread.reset(new std::thread(std::bind(&ThreadPool::thread_func, this)));
    threads.push_back(thread);
  }
}

void ThreadPool::RemoveAllTasks() {
  {
    std::lock_guard<std::mutex> guard(mutex_);
    for (auto& iter : task_list_) {
      iter.reset();
    }
    task_list_.clear();
  }
}

}  // namespace base
