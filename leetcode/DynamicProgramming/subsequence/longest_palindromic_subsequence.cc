#include <limits.h>
#include <algorithm>
#include <string>
#include <vector>

using std::vector;
using std::max;
using std::string;

// Problem: https://leetcode-cn.com/problems/longest-palindromic-subsequence/

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

class Solution {
 public:
  int longestPalindromeSubseq(string s) {
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
    for (int i = 0; i < s.size(); i++) dp[i][i] = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
      for (int j = i + 1; j < s.size(); j++) {
        if (s[i] == s[j]) {
          dp[i][j] = dp[i + 1][j - 1] + 2;
        } else {
          dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[0][s.size() - 1];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.longestPalindromeSubseq("bbbab");
  LOG(INFO) << ret;

  return 0;
}
