#include <vector>
#include <limits.h>
#include <algorithm>
#include <mutex>
#include <memory>
#include <condition_variable>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using std::vector;
using std::min;

class FooBar {
  private:
    int n;
    bool flag_;
    std::mutex mutex_;
    std::condition_variable cond_;

  public:
    FooBar(int n) {
        this->n = n;
        flag_ = false;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            std::unique_lock<mutex> lk(mutex_);
            cond_.wait(lk, [this]{return !flag_;});
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            flag_ = true;
            cond_.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            std::unique_lock<mutex> lk(mutex_);
            cond_.wait(lk, [this]{return flag_;});
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            flag_ = false;
            cond_.notify_one();
        }
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
