#include <algorithm>
#include <climits>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

/*
 * Problems: https://leetcode-cn.com/problems/coin-change-2/
 * 如果求组合数就是外层for循环遍历物品，内层for遍历背包。
 * 如果求排列数就是外层for遍历背包，内层for循环遍历物品。
 */

// 由完全背包转换
// 注意这个二维状态是使用 dp[n+1][m+1]
class Solution {
 public:
  int change(int amount, vector<int>& coins) {
    if (amount == 0) return 1;

    vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, 0));
    // 初始化
    dp[0][0] = 1;

    for (int i = 1; i <= coins.size(); ++i) {
      for (int j = 0; j <= amount; ++j) {
        // 必须分拆动态规划
        dp[i][j] = dp[i - 1][j];
        for (int k = 1; k <= j / coins[i - 1]; ++k) {
          dp[i][j] += dp[i - 1][j - k * coins[i - 1]];
          // 这样是错误的，有可能无法进入下面循环
          // dp[i][j] = dp[i-1][j] + dp[i-1][j - k*coins[i-1]];
        }
      }
    }
    return dp[coins.size()][amount];
  }
};

// version 1
class Solution1 {
 public:
  int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    // 遍历物品，必须先遍历coins，后遍历amount
    for (int i = 0; i < coins.size(); i++) {
      for (int j = coins[i]; j <= amount; j++) {  // 遍历背包
        dp[j] += dp[j - coins[i]];
      }
    }
    return dp[amount];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> coins({1, 2, 5});
  int amount = 100;

  Solution solu;
  int ret = solu.change(amount, coins);
  LOG(INFO) << ret;

  Solution1 solu1;
  ret = solu1.change(amount, coins);
  LOG(INFO) << ret;

  return 0;
}
