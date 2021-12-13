#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::max;

// DFS
class SolutionDFS {
 private:
  int bfs(const vector<int>& nums, int cur, int value, bool last) {
    // stop
    if (cur >= nums.size()) return value;

    // deep drill
    if (last) {
      value = bfs(nums, cur + 1, value, false);
    } else {
      value = max(bfs(nums, cur + 1, value, false),
                  bfs(nums, cur + 1, value + nums[cur], true));
    }

    return value;
  }

 public:
  int rob(vector<int>& nums) {
    int value = 0;
    int cur = 0;
    value = max(bfs(nums, cur, value + nums[cur], true),
                bfs(nums, cur, value, false));

    return value;
  }
};

// DFS + cache
class SolutionDFSCache {
 public:
  /* 记忆化dfs */
  /* 两个数组分别记录偷与不偷第i个房屋的情况下第i个房屋及之后能偷窃到的最大值 */
  /* 初始值设置为-1，表示不偷 */
  int st[109], nst[109];
  int rob(vector<int>& nums) {
    /* 初始化缓存数组 */
    for (int i = 0; i < nums.size(); ++i) {
      st[i] = -1;
      nst[i] = -1;
    }
    return dfs(nums, 0, false);
  }

  /* 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃 */
  int dfs(vector<int>& nums, int i, bool issteal) {
    /* i越界，没房屋可供偷窃，只能空手而归了>_< */
    if (i >= nums.size()) return 0;
    /* 前一个偷过了，那这个就不能偷了！去下一家看看~ */
    else if (issteal) {
      if (nst[i + 1] == -1) nst[i + 1] = dfs(nums, i + 1, false);
      return nst[i + 1];
    }
    /* 前一个没偷过，那么这个可偷可不偷，两者取大的那个 */
    else {
      if (st[i + 1] == -1) st[i + 1] = dfs(nums, i + 1, true);
      if (nst[i + 1] == -1) nst[i + 1] = dfs(nums, i + 1, false);
      return max(st[i + 1] + nums[i], nst[i + 1]);
    }
  }
};

// DP
class SolutionDP {
 public:
  /* 动态规划 */
  /* dp[i] 表示前i个房屋所能偷到的最大值 */
  int rob(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(nums.size(), 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], n > 1 ? nums[1] : 0);
    for (int i = 2; i < n; ++i) dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    return dp[n - 1];
  }
};

class Solution {
 public:
  /* 动态规划 + 滚动数组 */
  /* x, y, z 分别表示前i - 2， i - 1, i个房屋所能偷到的最大值 */
  int rob(vector<int>& nums) {
    int n = nums.size();
    int x = nums[0], y = max(nums[0], n > 1 ? nums[1] : 0), z;
    for (int i = 2; i < n; ++i) {
      z = max(x + nums[i], y);
      x = y;
      y = z;
    }
    return y;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {1, 2, 3, 1};
  int ret = solu.rob(nums);
  LOG(INFO) << ret;
  return 0;
}
