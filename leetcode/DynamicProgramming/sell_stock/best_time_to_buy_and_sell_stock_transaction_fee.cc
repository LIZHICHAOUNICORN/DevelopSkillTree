#include <vector>
#include <algorithm>
#include <limits.h>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::max;


class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int len = prices.size();
        if (len == 0) return 0;
        vector<vector<int>> dp(len, vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for(int i = 1; i < len; ++i) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i]);
            dp[i][1] = max(dp[i-1][0] + prices[i] - fee, dp[i-1][1]); 
        }
        return dp[len-1][1];

    }
};

class Solution {
 public:
  /*
   *
   dp[i][k][0 or 1]
   0 <= i <= n-1, 1 <= k <= K
   n 为天数，大 K 为最多交易数
   此问题共 n × K × 2 种状态，全部穷举就能搞定。
   
   for 0 <= i < n:
       for 1 <= k <= K:
           for s in {0, 1}:
               dp[i][k][s] = max(buy, sell, rest) 

   dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
                 max(   选择 rest  ,             选择 sell      )
   解释：今天我没有持有股票，有两种可能：
   要么是我昨天就没有持有，然后今天选择 rest，所以我今天还是没有持有；
   要么是我昨天持有股票，但是今天我 sell 了，所以我今天没有持有股票了。
   
   dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
                 max(   选择 rest  ,           选择 buy         )
   
   解释：今天我持有着股票，有两种可能：
   要么我昨天就持有着股票，然后今天选择 rest，所以我今天还持有着股票；
   要么我昨天本没有持有，但今天我选择 buy，所以今天我就持有股票了。

   base case: 
   dp[-1][k][0] = 0
   解释：因为 i 是从 0 开始的，所以 i = -1 意味着还没有开始，这时候的利润当然是 0 。
   dp[-1][k][1] = -infinity
   解释：还没开始的时候，是不可能持有股票的，用负无穷表示这种不可能。
   dp[i][0][0] = 0
   解释：因为 k 是从 1 开始的，所以 k = 0 意味着根本不允许交易，这时候利润当然是 0 。
   dp[i][0][1] = -infinity
   解释：不允许交易的情况下，是不可能持有股票的，用负无穷表示这种不可能。
   *
   * */
  int maxProfit(vector<int>& prices, int fee) {
     if (prices.empty() || prices.size() == 1) return 0;
     const int n = prices.size();
     vector<vector<int>> f(n+1, vector<int>(2, 0));
  
     // 第一天持有股票
     f[0][1] = -prices[0]-fee;
     // 第二天持有股票
     f[1][1] = max(-prices[0]-fee, -prices[1]-fee);
  
     // 第一天不持有股票
     f[0][0] = 0;
     // 第二天不持有股票
     f[1][0] = max(prices[1]-prices[0]-fee, 0);
  
     if (prices.size() == 2) {
         return max(f[1][0], f[1][1]);
     }
  
     int result = INT_MIN;
     for (int i = 2; i < n; i++) {
         f[i][0] = max(f[i - 1][1] + prices[i], f[i - 1][0]);
         f[i][1] = max(f[i - 1][1], f[i - 1][0] - prices[i]-fee);
         int cur_max = max(f[i][0], f[i][1]);
         if (cur_max > result) result = cur_max;
     }
     return result;
   }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> prices = {1,3,2,8,4,9};
  Solution solu;
  int ret = solu.maxProfit(prices, 2);
  LOG(INFO) << ret;
  return 0;
}
