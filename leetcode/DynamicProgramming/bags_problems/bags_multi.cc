#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

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
  int MaxValue2D(vector<int>& weight, vector<int>& value,
                 vector<int>& nums, const int bagWeight) {

    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] > 1) { // nums[i]保留到1，把其他物品都展开
            weight.push_back(weight[i]);
            value.push_back(value[i]);
            nums[i]--;
        }
    }

    vector<int> dp(bagWeight + 1, 0);
    for(int i = 0; i < weight.size(); i++) { // 遍历物品
        for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
            dp[j] = std::max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> weights{1, 3, 4};
  vector<int> values{15, 20, 30};
  vector<int> nums = {2, 3, 2};

  int bag_weight = 10;
  Solution solu;
  int max_value = solu.MaxValue2D(weights, values, nums, bag_weight);
  LOG(INFO) << "2D Max bag value is : " << max_value;

  return 0;
}
