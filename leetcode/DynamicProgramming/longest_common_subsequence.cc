#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::max;


void Print2DVector(vector<vector<long>>& two_d_vector) {
  for (vector<long> vecs : two_d_vector) {
    for (long value : vecs) {
      cout << value << "\t";
    }
    cout << endl;
  }
}

// fail
class Solution {
 public:
  int dfs(const string& s1, const string& s2, int i, int j,
          vector<vector<int>>& dp) {
      if (i == 0 || j == 0) return 0; // 决策边界

      if (dp[i][j] != -1) return dp[i][j];  // 记忆化

      // 状态转移
      dp[i][j] = max(dfs(s1, s2, i - 1, j, dp), dfs(s1, s2, i, j - 1, dp));
      if (s1[i-1] == s2[j-1])
          dp[i][j] = max(dp[i][j], dfs(s1, s2, i - 1, j - 1, dp) + 1);

      return dp[i][j];
  }

  int longestCommonSubsequence(string text1, string text2) {
      vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), -1));
      return dfs(text1, text2, text1.size()-1, text2.size()-1, dp);
  }
};

class Solution1 {
 public:
  string s1, s2;
  vector<vector<int>> dp;

  int dfs(int i, int j) {
    if (i == 0 || j == 0) return 0; // 决策边界

    if (dp[i][j] != -1) return dp[i][j];  // 记忆化

    // 状态转移
    dp[i][j] = max(dfs(i - 1, j), dfs(i, j - 1));
    if (s1[i-1] == s2[j-1])
        dp[i][j] = max(dp[i][j], dfs(i - 1, j - 1) + 1);

    return dp[i][j];
  }

  int longestCommonSubsequence(string text1, string text2) {
    s1 = text1;
    s2 = text2;
    dp = vector<vector<int>>(s1.size() + 1, vector<int>(s2.size() + 1, -1));
    return dfs(s1.size(), s2.size());
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.longestCommonSubsequence("ace", "abcde");
  LOG(INFO) << ret;
  return 0;
}
