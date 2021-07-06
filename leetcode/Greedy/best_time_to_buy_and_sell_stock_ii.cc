#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

class Solution {
public:
    // status: 目前是否有股票
    // index: 第几天
    // profix: 当前收益
    int GetProfit(vector<int>& prices, int index, bool status, int profit) {
        if (index >= prices.size()) return max(0, profit);
        if (status) {
            return max(GetProfit(prices, index+1, false,  profit+prices[index]),
                       GetProfit(prices, index+1, status, profit));
        }
            
        return max(GetProfit(prices, index+1, false, profit),
                   GetProfit(prices, index+1, true, profit-prices[index]));
    }
    int maxProfit(vector<int>& prices) {
        return GetProfit(prices, 0, false, 0);
    }
};

class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i-1];
            if (diff > 0) result += diff;
        }
        return result;
    }
};


class Solution1 {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 0) return 0;
        vector<vector<int>> dp(len, vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); ++i) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]-prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0]+prices[i]);
        }
        return dp[prices.size()-1][1];

    }
};

// dp + 滚动数组
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 0) return 0;
        vector<vector<int>> dp(2, vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); ++i) {
            dp[i%2][0] = max(dp[(i-1)%2][0], dp[(i-1)%2][1]-prices[i]);
            dp[i%2][1] = max(dp[(i-1)%2][1], dp[(i-1)%2][0]+prices[i]);
        }
        return dp[(len-1)%2][1];

    }
};

// greedy
class Solution3 {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i-1];
            if (diff > 0) result += diff;
        }
        return result;
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
