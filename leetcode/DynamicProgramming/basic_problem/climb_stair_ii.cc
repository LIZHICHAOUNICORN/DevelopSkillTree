// Author: Zhichao Li
// Time: 2021年06月08日

#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"


// Time O(n)
// Space O(n)
// 爬楼梯，每次可以1步，2步，3步，...m步
// 那么n层楼梯有多少中爬法。
class Solution {
public:
    int climb(int n) {
        std::vector<int> dp(n+1, 0);
        // dp[0] 是1 是没有一定理由的，是为了
        // 后续方程推导。
        dp[0] = 1
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 1; j < m; j++) {
              if (i - j >= 0) dp[i] += dp[i-j];
            }
        }
        return dp[n];
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.fib(2);
  LOG(INFO) << ret;
  return 0;
}
