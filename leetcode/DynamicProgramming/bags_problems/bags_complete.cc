#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;

/*
 * Problem:
 * 有N件物品和一个最多能背重量为W的背包。第i件物品的重量是weight[i]，得到的价值是value[i]。
 * 每件物品都有无限个（也就是可以放入背包多次），求解将哪些物品装入背包里物品价值总和最大。
 */

class Solution {
 public:
  int MaxValue1D(const vector<int>& weights, const vector<int>& values,
                 const int bag_weight) {
    vector<int> dp(bag_weight + 1, 0);
    for (int i = 0; i < weights.size(); ++i) {
      for (int j = weights[i]; j <= bag_weight; ++j) {
        dp[j] = std::max(dp[j], dp[j - weights[i]] + values[i]);
      }
    }
    return dp[bag_weight];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> weights{1, 3, 4};
  vector<int> values{15, 20, 30};
  int bag_weight = 4;

  Solution solu;
  int max_value = solu.MaxValue1D(weights, values, bag_weight);
  LOG(INFO) << max_value;
  return 0;
}
