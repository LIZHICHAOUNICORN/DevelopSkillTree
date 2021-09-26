#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::string;
using std::max;

class Solution {
 public:
  int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 1; i <= m; i++) {
      char c1 = word1[i - 1];
      for (int j = 1; j <= n; j++) {
        char c2 = word2[j - 1];
        if (c1 == c2) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }

    int lcs = dp[m][n];
    return m - lcs + n - lcs;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  auto ret = solu.minDistance("abc", "ahbgdc");
  LOG(INFO) << ret;
  return 0;
}
