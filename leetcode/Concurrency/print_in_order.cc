#include <limits.h>
#include <algorithm>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using std::vector;
using std::min;

class Foo {
 private:
  std::mutex first_mux_, second_mux_;
  std::condition_variable first_con_, second_con_;
  bool first_flag_, second_flag_;

 public:
  Foo() {
    first_flag_ = false;
    second_flag_ = false;
  }

  void first(function<void()> printFirst) {
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    std::unique_lock<mutex> lk(first_mux_);
    first_flag_ = true;
    first_con_.notify_one();
  }

  void second(function<void()> printSecond) {
    {
      std::unique_lock<mutex> lk(first_mux_);
      first_con_.wait(lk, [this] { return first_flag_; });
    }
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    std::unique_lock<mutex> lk(second_mux_);
    second_flag_ = true;
    second_con_.notify_one();
  }

  void third(function<void()> printThird) {
    {
      std::unique_lock<mutex> lk(second_mux_);
      second_con_.wait(lk, [this] { return second_flag_; });
    }
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
