#include <condition_variable>
#include <mutex>
#include <queue>

namespace util {

template <class T>
class Queue {
 public:
  void Push(const T& item) {
    {
      std::scoped_lock<std::mutex> lk(mutex_);
      tasks_.push(std::move(item));
    }
    cv_.notify_one();
  }
  void Push(T&& item) {
    {
      std::scoped_lock<std::mutex> lk(mutex_);
      tasks_.push(std::move(item));
    }
    cv_.notify_one();
  }
  bool Pop(T& item) {
    std::unique_lock<std::mutex> uniq_lk(mutex_);
    cv_.wait(uniq_lk, [this]() { return !this->tasks_.empty() || this->stop_; });
    if (tasks_.empty()) return false;
    item = std::move(tasks_.front());
    tasks_.pop();
    return true;
  }
  size_t Size() {
    std::scoped_lock<std::mutex> lk(mutex_);
    return tasks_.size();
  }
  bool Empty() {
    std::scoped_lock<std::mutex> lk(mutex_);
    return tasks_.empty();
  }

  void Stop() {
    {
      std::scoped_lock<std::mutex> lk(mutex_);
      stop_ = true;
    }
    cv_.notify_all();
  }

 private:
  std::mutex mutex_;
  std::condition_variable cv_;
  std::queue<T> tasks_;
  bool stop_ = false;
};

}  //  namespace util
