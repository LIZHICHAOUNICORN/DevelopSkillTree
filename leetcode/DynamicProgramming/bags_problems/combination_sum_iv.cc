#include <algorithm>
#include <climits>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/combination-sum-iv/
// Solution:
// https://leetcode-cn.com/problems/combination-sum-iv/solution/gong-shui-san-xie-yu-wan-quan-bei-bao-we-x0kn/

// 由完全背包转换
// 注意这个二维状态是使用 dp[n+1][m+1]
using ULL = unsigned long long;
class Solution {
 public:
  int combinationSum4(vector<int>& nums, int target) {
    int len = target;
    vector<vector<ULL>> f(len + 1, vector<ULL>(target + 1, 0));
    f[0][0] = 1;
    int ans = 0;
    for (int i = 1; i <= len; i++) {
      for (int j = 0; j <= target; j++) {
        for (auto x : nums) {
          if (j >= x) f[i][j] += f[i - 1][j - x];
        }
      }
      ans += f[i][target];
    }
    return ans;
  }
};

// version 1
class Solution1 {
 public:
  int combinationSum4(vector<int>& nums, int target) {
    vector<int> f(target + 1, 0);  // or vector<unsigned long long> f(target +
                                   // 1,0); 就不用做取模的操作了
    f[0] = 1;
    for (int i = 1; i <= target; i++) {
      for (auto x : nums) {
        // c++计算的中间结果会溢出，但因为最终结果是int
        //因此每次计算完都对INT_MAX取模，0LL是将计算结果提升到long long类型
        if (i >= x) f[i] = (0LL + f[i] + f[i - x]);
      }
    }
    return f[target];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> coins({1, 2, 5});
  int amount = 100;

  Solution solu;
  int ret = solu.combinationSum4(coins, amount);
  LOG(INFO) << ret;

  Solution1 solu1;
  ret = solu1.combinationSum4(coins, amount);
  LOG(INFO) << ret;

  return 0;
}
