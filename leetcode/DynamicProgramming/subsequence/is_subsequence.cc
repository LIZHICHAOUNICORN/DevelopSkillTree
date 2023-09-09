#include <algorithm>
#include <vector>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/is-subsequence/

using std::vector;
using std::max;
using std::string;

// 模拟
class Solution {
 public:
  bool isSubsequence(string s, string t) {
    if (s.empty()) return true;
    if (s.size() > t.size()) return false;

    int start = 0;
    for (int i = 0; i < t.size(); ++i) {
      if (s[start] == t[i]) {
        ++start;
        if (start == s.size()) return true;
      }
    }
    return false;
  }
};

// DP
class Solution1 {
 public:
  bool isSubsequence(string s, string t) {
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
    for (int i = 1; i <= s.size(); i++) {
      for (int j = 1; j <= t.size(); j++) {
        if (s[i - 1] == t[j - 1])
          dp[i][j] = dp[i - 1][j - 1] + 1;
        else
          dp[i][j] = dp[i][j - 1];
      }
    }
    if (dp[s.size()][t.size()] == s.size()) return true;
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
