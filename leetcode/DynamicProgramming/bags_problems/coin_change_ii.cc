#include <algorithm>
#include <climits>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

/*
 * Problems: https://leetcode-cn.com/problems/coin-change-2/
 * 如果求组合数就是外层for循环遍历物品，内层for遍历背包。
 * 如果求排列数就是外层for遍历背包，内层for循环遍历物品。
 */

// version 1
class Solution {
 public:
  int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < coins.size();
         i++) {  // 遍历物品，必须先遍历coins，后遍历amount
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
  int amount = 12;

  Solution solu;
  int ret = solu.change(amount, coins);
  LOG(INFO) << ret;

  return 0;
}
