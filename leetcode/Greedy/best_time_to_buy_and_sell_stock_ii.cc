#include <cassert>
#include <vector>
#include <map>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::map;
using std::vector;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int profit = 0;
    if (prices.size() < 2) return profit;
    for (size_t i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i-1]) {
          profit += prices[i] - prices[i-1];
        }
    }
    return profit;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> bills = {7,1,5,3,6,4};
  int ret = solu.maxProfit(bills);
  LOG(INFO) << ret;
  return 0;
}
