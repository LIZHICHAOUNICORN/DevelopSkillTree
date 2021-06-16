#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

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


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> prices = {7,1,5,3,6,4};
  Solution solu;
  int ret = solu.maxProfit(prices);
  LOG(INFO) << ret;
  return 0;
}
