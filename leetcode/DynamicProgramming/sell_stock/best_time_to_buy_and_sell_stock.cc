#include <vector>
#include <climits>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int profit = 0;
    for (size_t i = 0; i < prices.size(); ++i) {
      for (size_t j = i; j < prices.size(); ++j) {
        if (profit < prices[j] - prices[i]) {
          profit = prices[j] - prices[i];
        }
      }
    }
    return profit;
  }
};

class Solution1 {
 public:
  int maxProfit(vector<int>& prices) {
    int low = INT_MAX;
    int result = 0;
    for (int i = 0; i < prices.size(); i++) {
      low = min(low, prices[i]);              // 取最左最小价格
      result = max(result, prices[i] - low);  // 直接取最大区间利润
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> prices = {7, 1, 5, 3, 6, 4};
  Solution solu;
  int ret = solu.maxProfit(prices);
  LOG(INFO) << ret;
  return 0;
}
