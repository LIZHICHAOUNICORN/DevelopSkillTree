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

class ZeroEvenOdd {
 private:
  int n;
  std::mutex mutex_;
  std::condition_variable zero_con_, other_con_;
  int number_;

 public:
  ZeroEvenOdd(int n) {
    this->n = n;
    number_ = n;
  }

  // printNumber(x) outputs "x", where x is an integer.
  void zero(function<void(int)> printNumber) {}

  void even(function<void(int)> printNumber) {}

  void odd(function<void(int)> printNumber) {}
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
