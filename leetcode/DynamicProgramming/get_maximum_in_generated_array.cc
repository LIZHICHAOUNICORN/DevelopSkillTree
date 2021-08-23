#include <vector>
#include <limits.h>
#include <algorithm>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using std::vector;
using std::min;

// Problem: https://leetcode-cn.com/problems/get-maximum-in-generated-array

class Solution {
 public:
  int getMaximumGenerated(int n) {
      if (n <= 1) return n;
      vector<int> dp(n+1, 0);
      dp[0] = 0;
      dp[1] = 1;
      int max_value = dp[1];
      for (int k = 2; k <= n; ++k) {
          if (k % 2 == 0) {
              int i = k / 2;
              dp[k] = dp[i];
          } else {
              int i = (k - 1)/2;
              dp[k] = dp[i] + dp[i+1];
          }
          if (dp[k] > max_value) max_value = dp[k];
      }
      return max_value;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
