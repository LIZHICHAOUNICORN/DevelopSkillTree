#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;

/*
 * Problems:
 *  有N件物品和一个最多能被重量为W 的背包。
 *  第i件物品的重量是weight[i]，得到的价值是value[i]，
 *  每件物品只能用一次，求解将哪些物品装入背包里物品价值总和最大。
 */

// version 1
// dp[i][j] = max(dp[i-1][j], dp[i-1][j-weights[i]] + values[i])
class Solution {
 public:
  int MaxValue2D(const vector<int>& weights, const vector<int>& values,
                 const int bag_weight) {
    // dp array
    int m = weights.size();
    int n = bag_weight + 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // initial
    for (int j = weights[0]; j <= bag_weight; j++) {
      dp[0][j] = values[0];
    }

    // Number of weights;
    for (int i = 1; i < weights.size(); ++i) {
      for (int j = 0; j <= bag_weight; ++j) {
        if (j < weights[i]) {
          dp[i][j] = dp[i - 1][j];
        } else {
          dp[i][j] =
              std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
        }
      }
    }

    return dp[m - 1][n - 1];
  }
};

class Solution1 {
 public:
  int MaxValue1D(const vector<int>& weights, const vector<int>& values,
                 const int bag_weight) {
    vector<int> dp(bag_weight + 1, 0);
    for (int i = 0; i < weights.size(); ++i) {
      for (int j = bag_weight; j >= weights[i]; --j) {
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
  int max_value = solu.MaxValue2D(weights, values, bag_weight);
  LOG(INFO) << "2D Max bag value is : " << max_value;

  return 0;
}
