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


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> prices = {7,1,5,3,6,4};
  Solution solu;
  int ret = solu.maxProfit(prices);
  LOG(INFO) << ret;
  return 0;
}
