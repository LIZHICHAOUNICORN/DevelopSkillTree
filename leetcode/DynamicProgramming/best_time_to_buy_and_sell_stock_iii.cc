#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::max;

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
  int maxProfit(vector<int> &prices) {
    const int inf = 1 << 30;
    const int n = prices.size();
    int f[30000 + 5][3][2];
    for (int i = 0; i <= n; i++) {
      f[i][0][0] = 0;
      f[i][0][1] = -inf;
    }
    for (int i = 1; i <= 2; i++) {
      f[0][i][0] = -inf;
      f[0][i][1] = -inf;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= 2; j++) {
        f[i][j][0] = max(f[i - 1][j][1] + prices[i - 1], f[i - 1][j][0]);
        if (j) {
          f[i][j][1] = max(f[i - 1][j][1], f[i - 1][j - 1][0] - prices[i - 1]);
        }
      }
    }
    return max(max(f[n][0][0], f[n][1][0]), f[n][2][0]);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> prices = {7,1,5,3,6,4};
  Solution solu;
  int ret = solu.maxProfit(prices);
  LOG(INFO) << ret;
  return 0;
}
