#include <limits.h>
#include <algorithm>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::string;
using std::min;

// Problem: https://leetcode-cn.com/problems/valid-parenthesis-string/

class Solution {
 public:
  bool checkValidString(string s) {
    int n = s.size();
    vector<vector<bool>> dp = vector<vector<bool>>(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
      if (s[i] == '*') {
        dp[i][i] = true;
      }
    }

    for (int i = 1; i < n; i++) {
      char c1 = s[i - 1];
      char c2 = s[i];
      dp[i - 1][i] = (c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*');
    }

    for (int i = n - 3; i >= 0; i--) {
      char c1 = s[i];
      for (int j = i + 2; j < n; j++) {
        char c2 = s[j];
        if ((c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*')) {
          dp[i][j] = dp[i + 1][j - 1];
        }
        for (int k = i; k < j && !dp[i][j]; k++) {
          dp[i][j] = dp[i][k] && dp[k + 1][j];
        }
      }
    }
    return dp[0][n - 1];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
