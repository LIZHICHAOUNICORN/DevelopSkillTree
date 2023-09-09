#include <algorithm>
#include <climits>
#include <map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/burst-balloons/
// Solution:
// https://leetcode-cn.com/problems/burst-balloons/solution/ni-xiang-si-wei-cong-bao-li-hui-su-dao-ji-yi-hua-b/
// https://leetcode-cn.com/problems/burst-balloons/solution/chao-xiang-xi-hui-su-dao-fen-zhi-dao-dp-by-niu-you/
// https://leetcode-cn.com/problems/burst-balloons/solution/chuo-qi-qiu-by-leetcode-solution/

using namespace std;

// backtrack
class Solution {
 private:
  int helper(vector<int>& a, int i, int j) {
    int max_value = 0;

    // 注意每次从(i, j)中取一个气球，但不包括i和j
    // 穷尽所有放置方案，得到一个最大的方案max
    for (int k = i + 1; k < j; k++) {
      max_value = max(max_value,
                      helper(a, i, k) + a[i] * a[k] * a[j] + helper(a, k, j));
    }
    return max_value;
  }

 public:
  int maxCoins(vector<int>& nums) {
    vector<int> a(nums.size() + 2);
    a[0] = 1;
    a[a.size() - 1] = 1;
    for (int i = 0; i < nums.size(); i++) {
      a[i + 1] = nums[i];
    }
    return helper(a, 0, a.size() - 1);
  }
};

class Solution1 {
 private:
  int helper(vector<int>& a, int i, int j, vector<vector<int>>& mem) {
    int max_value = 0;
    if (mem[i][j] != -1) return mem[i][j];

    // 注意每次从(i, j)中取一个气球，但不包括i和j
    // 穷尽所有放置方案，得到一个最大的方案max
    for (int k = i + 1; k < j; k++) {
      max_value = max(max_value, helper(a, i, k, mem) + a[i] * a[k] * a[j] +
                                     helper(a, k, j, mem));
    }
    mem[i][j] = max_value;
    return max_value;
  }

 public:
  int maxCoins(vector<int>& nums) {
    vector<int> a(nums.size() + 2);
    vector<vector<int>> mem(a.size(), vector<int>(a.size(), -1));
    a[0] = 1;
    a[a.size() - 1] = 1;
    for (int i = 0; i < nums.size(); i++) {
      a[i + 1] = nums[i];
    }
    return helper(a, 0, a.size() - 1, mem);
  }
};


// 动态规划
class Solution2 {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> rec(n + 2, vector<int>(n + 2));
        vector<int> val(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 2; j <= n + 1; j++) {
                for (int k = i + 1; k < j; k++) {
                    int sum = val[i] * val[k] * val[j];
                    sum += rec[i][k] + rec[k][j];
                    rec[i][j] = max(rec[i][j], sum);
                }
            }
        }
        return rec[0][n + 1];
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums({8, 2, 6, 8, 9, 8, 1, 4, 1, 5, 3, 0, 7, 7, 0, 4, 2, 2});

  Solution solu;
  int ret = solu.maxCoins(nums);
  LOG(INFO) << ret;
  return 0;
}
