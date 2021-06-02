#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(input, 8, "The test case");

class Solution {
 public:
  bool isPerfectSquare(int num) {
    int value = mySqrt(num);
    return value * value == num;
  }
 private:
  int mySqrt(int x) {
    if (x <= 1) return x;
    int left = 1, right = x;
    long long mid = left + (right - left) / 2;
    while (left < right) {
      if (mid * mid > x) right = mid - 1;
      else if (mid * mid < x) left = mid + 1;
      else return mid;
      mid = left + (right - left) / 2;
    }
    long long aa = (long long) left * left;
    return aa > x ? left - 1 : left;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.isPerfectSquare(FLAGS_input);
  LOG(INFO) << ret;
  return 0;
}
