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

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size()+1, vector<int>(text2.size()+1, 0));
        for (int i = 1; i <= text1.size(); i++) {
            for(int j = 1; j <= text2.size(); ++j) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[text1.size()][text2.size()];


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
