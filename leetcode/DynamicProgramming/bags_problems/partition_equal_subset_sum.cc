// Time: 2021年06月13日
// Author: Zhichao Li

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using std::vector;

// Problem: https://leetcode-cn.com/problems/partition-equal-subset-sum/
// Solution:
// https://leetcode-cn.com/problems/partition-equal-subset-sum/solution/0-1-bei-bao-wen-ti-xiang-jie-zhen-dui-ben-ti-de-yo/

// base version, 2D dp
class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    sum = sum / 2;

    vector<vector<bool>> dp(nums.size(), vector<bool>(sum + 1, false));
    // 因为候选数 nums[0] 是正整数，凑不出和为0
    dp[0][0] = false;
    if (nums[0] <= sum) dp[0][nums[0]] = true;

    for (int i = 1; i < nums.size(); ++i) {
      for (int j = 0; j <= sum; ++j) {
        // 最差就是这次nums[i] 不放入，维持之前的状态
        dp[i][j] = dp[i - 1][j];
        // 如果签好num[i] 是当前的重量
        if (nums[i] == j) {
          dp[i][j] = true;
          continue;
        }
        // 如果nums[i] 小于需要的重量，
        // 那么去上个或者取之前的
        if (nums[i] < j) {
          dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
        }
      }
    }
    return dp[nums.size() - 1][sum];
  }
};


// 1D dp
class Solution1 {
 public:
  bool canPartition(vector<int>& nums) {
    int sum = 0;
    // Sum
    for (auto iter = nums.cbegin(); iter != nums.cend(); ++iter) {
      sum += *iter;
    }
    if (sum % 2 == 1) return false;
    vector<int> dp(10001, 0);

    int target = sum / 2;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = target; j >= nums[i]; --j) {
        dp[j] = std::max(dp[j], dp[j - nums[i]] + nums[i]);
      }
    }
    if (dp[target] == target) return true;
    return false;
  }
};

// version 2
class Solution2 {
 public:
  bool canPartition(vector<int>& nums) {
    if (nums.size() < 2) return false;

    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    //        for (auto iter = nums.cbegin(); iter != nums.cend(); ++iter) {
    //            sum += *iter;
    //        }

    if (0 != (1 & sum)) return false;
    //      if (sum % 2 == 1) return false;

    int target = sum / 2;
    int max = *(std::max_element(nums.begin(), nums.end()));
    if (max > target) return false;

    // Dont know why this operation.
    //        std::bitset<((200 * 100) >> 1) + 1> alpha(1);
    //        for (auto n : nums) {
    //            alpha |= (alpha << n);
    //        }
    //        return 1 == alpha[sum >> 1];

    vector<int> dp(10001, 0);
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = target; j >= nums[i]; --j) {
        dp[j] = std::max(dp[j], dp[j - nums[i]] + nums[i]);
      }
    }
    if (dp[target] == target) return true;
    return false;
  }
};

int main(int argc, char* argv[]) {
  Solution solu;
  vector<int> nums({1, 5, 11, 5});
  bool ret = solu.canPartition(nums);
  std::cout << "Result : " << ret << std::endl;
  return 0;
}
