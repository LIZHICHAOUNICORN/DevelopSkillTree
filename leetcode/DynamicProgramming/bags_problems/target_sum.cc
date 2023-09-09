#include <algorithm>
#include <iostream>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/target-sum/
// Solutions:
// https://leetcode-cn.com/problems/target-sum/solution/gong-shui-san-xie-yi-ti-si-jie-dfs-ji-yi-et5b/

// backtrack version
// Time: O(2^n)
// Space: O(n)
class Solution {
 public:
  int count = 0;

  int findTargetSumWays(vector<int>& nums, int target) {
    backtrack(nums, target, 0, 0);
    return count;
  }

  void backtrack(vector<int>& nums, int target, int index, int sum) {
    if (index == nums.size()) {
      if (sum == target) {
        count++;
      }
    } else {
      backtrack(nums, target, index + 1, sum + nums[index]);
      backtrack(nums, target, index + 1, sum - nums[index]);
    }
  }
};

// 原始方法
class Solution3 {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (std::abs(target) > sum) return 0;

    int m = nums.size() + 1;
    int n = sum * 2 + 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // dp[0][0+sum]: nums中前0个， 其求和为0时的方法数为1；
    dp[0][0 + sum] = 1;

    for (int i = 1; i < m; i++) {
      int x = nums[i - 1];
      for (int j = -sum; j <= sum; j++) {
        if ((j - x) + sum >= 0) dp[i][j + sum] += dp[i - 1][(j - x) + sum];
        if ((j + x) + sum <= 2 * sum)
          dp[i][j + sum] += dp[i - 1][(j + x) + sum];
      }
    }
    return dp[m - 1][sum + target];
  }
};

// DP version, 2D
class Solution1 {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    int sum = 0;
    for (int& num : nums) {
      sum += num;
    }
    int diff = sum - target;
    if (diff < 0 || diff % 2 != 0) {
      return 0;
    }
    int n = nums.size(), neg = diff / 2;
    vector<vector<int>> dp(n + 1, vector<int>(neg + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
      int num = nums[i - 1];
      for (int j = 0; j <= neg; j++) {
        dp[i][j] = dp[i - 1][j];
        if (j >= num) {
          dp[i][j] += dp[i - 1][j - num];
        }
      }
    }
    return dp[n][neg];
  }
};

// DP version  1D
class Solution2 {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    int sum = 0;
    for (int& num : nums) {
      sum += num;
    }
    int diff = sum - target;
    if (diff < 0 || diff % 2 != 0) {
      return 0;
    }
    int neg = diff / 2;
    vector<int> dp(neg + 1);
    dp[0] = 1;
    for (int& num : nums) {
      for (int j = neg; j >= num; j--) {
        dp[j] += dp[j - num];
      }
    }
    return dp[neg];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution3 solu;
  vector<int> nums({1, 1, 1, 1, 1});
  int target = 3;
  int ret = solu.findTargetSumWays(nums, target);
  std::cout << "TargetSumWays: " << ret << std::endl;

  return 0;
}
