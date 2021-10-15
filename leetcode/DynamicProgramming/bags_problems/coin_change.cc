#include <algorithm>
#include <vector>
#include <climits>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

/*
 * Problems: https://leetcode-cn.com/problems/coin-change/
 */

// version 1
class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    int Max = amount + 1;
    vector<int> dp(amount + 1, Max);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
      for (int j = 0; j < (int)coins.size(); ++j) {
        if (coins[j] <= i) {
          dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
      }
    }
    return dp[amount] > amount ? -1 : dp[amount];
  }
};

// version 2
class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i < coins.size(); i++) {      // 遍历物品
      for (int j = coins[i]; j <= amount; j++) {  // 遍历背包
        if (dp[j - coins[i]] != INT_MAX) {  // 如果dp[j - coins[i]]是初始值则跳过
          dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
        }
      }
    }
    if (dp[amount] == INT_MAX) return -1;
    return dp[amount];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> coins({1, 2, 5});
  int amount = 12;

  Solution solu;
  int ret = solu.coinChange(coins, amount);
  LOG(INFO) << ret;

  Solution1 solu1;
  ret = solu1.coinChange(coins, amount);
  LOG(INFO) << ret;

  return 0;
}
