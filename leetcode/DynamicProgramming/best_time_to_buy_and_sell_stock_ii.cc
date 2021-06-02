#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int profit = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
      if (prices[i] - prices[i-1] > 0) {
        profit += prices[i] - prices[i-1];
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
