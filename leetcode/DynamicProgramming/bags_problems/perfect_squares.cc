#include <algorithm>
#include <climits>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/perfect-squares/

// 完全背包解法
class Solution {
 public:
  int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i <= n; i++) {        // 遍历背包
      for (int j = 1; j * j <= i; j++) {  // 遍历物品
        dp[i] = min(dp[i - j * j] + 1, dp[i]);
      }
    }
    return dp[n];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.numSquares(100);
  LOG(INFO) << ret;

  return 0;
}
