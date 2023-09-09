#include <iostream>

#include <gflags/gflags.h>
#include <glog/logging.h>

class Solution {
 public:
  int climbStairs(int n) {
    if (n <= 2) return n;
    int pre = 1;
    int cur = 2;
    int ret = 0;
    for (int i = 2; i < n; ++i) {
      ret = cur + pre;
      pre = cur;
      cur = ret;
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
