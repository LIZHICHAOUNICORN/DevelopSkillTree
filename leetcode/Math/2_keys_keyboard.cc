#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;
// Problem: https://leetcode-cn.com/problems/2-keys-keyboard

class Solution {
 public:
  int minSteps(int n) {
    int ret = 0;
    for (int i = 2; i * i < n; ++i) {
      while (n % i == 0) {
        n /= i;
        ret += i;
      }
    }
    if (n > 1) ret += n;
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  for (int i = 3; i < 1000; ++i) {
    int ret = solu.minSteps(i);
    LOG(INFO) << "ret: " << ret;
  }
  return 0;
}
