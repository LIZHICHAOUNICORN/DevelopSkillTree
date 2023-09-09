#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::min;
using std::string;
using std::swap;
using std::vector;

// Problems: https://leetcode.cn/problems/flip-string-to-monotone-increasing/

// DP
class Solution {
 public:
  // dp[i][j]表示以数字j为结尾，[0, i]为单调递增需要翻转的最小次数
  int minFlipsMonoIncr(string s) {
    int n = s.size();
    vector<vector<int> > dp(n, vector<int>(n, INT_MAX));
    // 默认第一位为0时
    dp[0][0] = 0, dp[0][1] = 1;
    // 如果第一位为1，则需要交换
    if (s[0] == '1') {
      swap(dp[0][0], dp[0][1]);
    }
    for (int i = 1; i < n; ++i) {
      if (s[i] == '0') {
        // 以0为结尾，不需要翻转
        dp[i][0] = dp[i - 1][0];
        // 以1为结尾，当前位翻转一次，前缀串可以0或1结尾，取最小
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
      } else {
        // 以0为结尾，当前位翻转，并且前缀串必须以0结尾
        dp[i][0] = dp[i - 1][0] + 1;
        // 以1结尾，不需要翻转，前缀串可以0或1结尾
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
      }
    }
    // 取两者情况之最小
    return min(dp[n - 1][0], dp[n - 1][1]);
  }
};

// 状态压缩
class Solution1 {
 public:
  int minFlipsMonoIncr(string s) {
    int n = s.size();
    int dp0 = 0, dp1 = 1;
    if (s[0] == '1') {
      swap(dp0, dp1);
    }
    for (int i = 1; i < n; ++i) {
      // 临时变量保存，后面会被覆盖
      int tmp1 = dp0, tmp2 = min(dp0, dp1);
      if (s[i] == '0') {
        dp1 = tmp2 + 1;
      } else {
        dp0 = dp0 + 1;
        dp1 = tmp2;
      }
    }
    return min(dp0, dp1);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string s("001100");
  int ret = solu.minFlipsMonoIncr(s);
  LOG(INFO) << ret;
  return 0;
}
