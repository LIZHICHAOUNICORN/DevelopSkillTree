#include <algorithm>
#include <climits>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/climbing-stairs/

// 完全背包解法

class Solution {
 private:
  int m = 2;
 public:
  int climbStairs(int n) {
    if (n <= 2) return n;

    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (i >= j) dp[i] += dp[i - j];
      }
    }

    return dp[n];
  }
};

class Solution1 {
 public:
  int climbStairs(int n) {
    if (n <= 2) return n;
    int pre = 1;
    int cur = 2;
    int next = 0;
    for (int i = 3; i <= n; ++i) {
      next = pre + cur;
      pre = cur;
      cur = next;
    }
    return next;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution1 solu;
  int ret = solu.climbStairs(100);
  LOG(INFO) << ret;

  return 0;
}
