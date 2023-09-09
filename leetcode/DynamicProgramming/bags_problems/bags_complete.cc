#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

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

// 2D
// dp[i][j] = max(dp[i-1][j], dp[i][j-weights[i]] + values[i])
class Solution1 {
 public:
  int MaxValue2D(const vector<int>& weights, const vector<int>& values,
                 const int bag_weight) {
    // dp array
    int m = weights.size();
    int n = bag_weight + 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // initial
    for (int j = 0; j <= bag_weight; j++) {
      // 显然当只有一件物品的时候，在容量允许的情况下，能选多少件就选多少件
      int maxK = j / weights[0];
      dp[0][j] = maxK * values[0];
    }

    // Number of weights;
    for (int i = 1; i < weights.size(); ++i) {
      for (int j = 0; j <= bag_weight; ++j) {
        for (int k = 1; k <= j / weights[i]; k++) {
          dp[i][j] = std::max(dp[i - 1][j],
                              dp[i - 1][j - k * weights[i]] + k * values[i]);
        }
      }
    }

    return dp[m - 1][n - 1];
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

  Solution1 solu1;
  int max_value1 = solu1.MaxValue2D(weights, values, bag_weight);
  LOG(INFO) << max_value << " " << max_value1;
  return 0;
}
