// Author: Zhichao Li
// Time: 2021年06月08日
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// https://leetcode-cn.com/problems/min-cost-climbing-stairs/

// Time O(n)
// Space O(1)
class Solution {
 public:
  // dp[n]到达第n层楼的最低花费
  // dp[n]=min(d[n-2],d[n-1])+cost[n-1]

  int minCostClimbingStairs(vector<int>& cost) {
    int prev = cost[0];
    int curr = cost[1];
    int result = 0;
    for (int i = 2; i < cost.size(); ++i) {
      result = min(prev, curr) + cost[i];
      prev = curr;
      curr = result;
    }
    return min(prev, curr);
  }
};

class Solution1 {
 public:
  int minCostClimbingStairs(vector<int>& cost) {
    if (cost.size() == 0) return 0;
    std::vector<size_t> dp(cost.size(), 0);
    dp[0] = cost[0];
    dp[1] = cost[1];
    for (size_t i = 2; i < cost.size(); ++i) {
      dp[i] = std::min(dp[i - 1], dp[i - 2]) + cost[i];
    }
    return std::min(dp[cost.size() - 1], dp[cost.size() - 2]);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  std::vector<int> cost({10, 15, 20});

  int ret = solu.minCostClimbingStairs(cost);
  LOG(INFO) << ret;
  return 0;
}
