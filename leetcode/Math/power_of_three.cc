#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/power-of-three/

class Solution {
 public:
  bool isPowerOfThree(int n) { return n > 0 && 1162261467 % n == 0; }
};

class Solution1 {
 public:
  bool isPowerOfThree(int n) {
    while (n && n % 3 == 0) {
      n /= 3;
    }
    return n == 1;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  for (int i = 3; i < 1000; ++i) {
    int ret = solu.isPowerOfThree(i);
    LOG(INFO) << "ret: " << ret;
  }
  return 0;
}
