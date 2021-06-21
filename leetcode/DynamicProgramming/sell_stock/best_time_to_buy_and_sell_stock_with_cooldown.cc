#include <vector>
#include <algorithm>
#include <limits.h>
#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::max;


class Solution {
 public:
  /*
    第一，当前持有股票
        a,昨天如果持有股票，那么今天就保留 hold[n - 1]
        b,前天出售个票，今天买入 unhold[n - 2] - prices[n]
        hold[n]=max(a,b)
    
    第二，当前没有股票
        a，昨天如果持有股票，那么今天就卖出 hold[n - 1] + prices[n]
        b，昨天没有持有股票，今天也没有 unhold[n - 1]
        unhold[n] = max(a,b)
    最后 max(hold[n], unhold[n])

   * */
  int maxProfit(vector<int>& prices) {
    if (prices.size() == 0 or prices.size() == 1) {
      return 0;
    }
    vector<int> hold(prices.size());
    //需要初始化到2，因为n - 2
    hold[0] = -prices[0];
    hold[1] = max(-prices[0], -prices[1]);
    vector<int> unhold(prices.size());
    //需要初始化到2，因为n - 2
    unhold[0] = 0;
    unhold[1] = max(prices[1] - prices[0], 0);
    if (prices.size() == 2) {
      return max(hold[1], unhold[1]);
    }
    int result = INT_MIN;
    for (int i = 2; i < prices.size(); ++i) {
      //0，1已经赋值了，从2开始
      hold[i] = max(hold[i - 1], unhold[i - 2] - prices[i]);
      unhold[i] = max(hold[i - 1] + prices[i], unhold[i - 1]);
      int cur_max = max(hold[i], unhold[i]);
      if (cur_max > result) {
        result = cur_max;
      }
    }
    return result;
  }
};

class Solution1 {
 public:
  int maxProfit(vector<int> &prices) {
   if (prices.empty() || prices.size() == 1) return 0;
   const int n = prices.size();
   vector<vector<int>> f(n+1, vector<int>(2, 0));
 
   // 第一天持有股票
   f[0][1] = -prices[0];
   // 第二天持有股票
   f[1][1] = max(-prices[0], -prices[1]);
 
   // 第一天不持有股票
   f[0][0] = 0;
   // 第二天不持有股票
   f[1][0] = max(prices[1]-prices[0], 0);
 
   if (prices.size() == 2) {
       return max(f[1][0], f[1][1]);
   }
 
   int result = INT_MIN;
   for (int i = 2; i < n; i++) {
       f[i][0] = max(f[i - 1][1] + prices[i], f[i - 1][0]);
       f[i][1] = max(f[i - 1][1], f[i - 2][0] - prices[i]);
       int cur_max = max(f[i][0], f[i][1]);
       if (cur_max > result) result = cur_max;
   }
   return result;
   }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(4, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        dp[0][2] = 0;
        dp[0][3] = 0;
        for (int i = 1; i < len; ++i) {
            dp[i][0] = max(max(dp[i-1][1]-prices[i], dp[i-1][3]-prices[i]), dp[i-1][0]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][3]);
            dp[i][2] = dp[i-1][0] + prices[i];
            dp[i][3] = dp[i-1][2];
        }
        return max(dp[len - 1][3],max(dp[len - 1][1], dp[len - 1][2]));

    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> prices = {7,1,5,3,6,4};
  Solution1 solu;
  int ret = solu.maxProfit(prices);
  LOG(INFO) << ret;
  return 0;
}
