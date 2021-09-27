#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/uncrossed-lines/

using std::vector;
using std::max;

class Solution {
 public:
  int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
      int num1 = nums1[i - 1];
      for (int j = 1; j <= n; j++) {
        int num2 = nums2[j - 1];
        if (num1 == num2) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[m][n];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int ret = solu.maxSubArray(nums);
  LOG(INFO) << ret;
  return 0;
}