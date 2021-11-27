#include <algorithm>
#include <numeric>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;

// Problem: https://leetcode-cn.com/problems/last-stone-weight-ii/
// https://leetcode-cn.com/problems/last-stone-weight-ii/solution/yi-pian-wen-zhang-chi-tou-bei-bao-wen-ti-5lfv/
// https://leetcode-cn.com/problems/last-stone-weight-ii/solution/zui-hou-yi-kuai-shi-tou-de-zhong-liang-i-95p9/

// basic version
class Solution {
 public:
  int lastStoneWeightII(vector<int>& stones) {
    int sum = accumulate(stones.begin(), stones.end(), 0);
    int n = stones.size(), m = sum / 2;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    dp[0][0] = true;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= m; ++j) {
        if (j < stones[i]) {
          dp[i + 1][j] = dp[i][j];
        } else {
          dp[i + 1][j] = dp[i][j] || dp[i][j - stones[i]];
        }
      }
    }
    int ret = 0;
    for (int j = m;; --j) {
      if (dp[n][j]) {
        ret = sum - 2 * j;
        break;
      }
    }
    return ret;
  }
};

class Solution1 {
 public:
  int lastStoneWeightII(vector<int>& stones) {
    int sum = accumulate(stones.begin(), stones.end(), 0);
    int m = sum / 2;
    vector<int> dp(m + 1);
    dp[0] = true;
    for (int weight : stones) {
      for (int j = m; j >= weight; --j) {
        dp[j] = dp[j] || dp[j - weight];
      }
    }
    for (int j = m;; --j) {
      if (dp[j]) {
        return sum - 2 * j;
      }
    }
  }
};

// DP, 1D
class Solution2 {
 public:
  int lastStoneWeightII(vector<int>& stones) {
    vector<int> dp((30 * 100 >> 1) + 1, 0);
    int sum = std::accumulate(stones.begin(), stones.end(), 0);
    int target = sum / 2;
    for (int i = 0; i < stones.size(); ++i) {
      for (int j = target; j >= stones[i]; --j) {
        dp[j] = std::max(dp[j], dp[j - stones[i]] + stones[i]);
      }
    }

    return sum - dp[target] - dp[target];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> stones({2,7,4,1,8,1});

  Solution solu;
  int ret = solu.lastStoneWeightII(stones);
  LOG(INFO) << ret;
  return 0;
}
