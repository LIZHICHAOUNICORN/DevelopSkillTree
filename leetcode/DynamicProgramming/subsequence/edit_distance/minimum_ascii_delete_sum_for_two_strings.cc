#include <vector>
#include <limits.h>
#include <string>
#include <algorithm>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using std::vector;
using std::string;
using std::min;

// Problem: https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/

class Solution {
 public:
  int minimumDeleteSum(string s1, string s2) {
      const int size1 = s1.size();
      const int size2 = s2.size();

      vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));

      for (int i = 1; i <= size1; ++i) {
          dp[i][0] = dp[i - 1][0] + int(s1[i - 1]);
      }

      for (int j = 1; j <= size2; ++j) {
          dp[0][j] = dp[0][j - 1] + int(s2[j - 1]);
      }

      for (int i = 1; i <= size1; ++i) {
          for (int j = 1; j <= size2; ++j) {
              dp[i][j] = min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
              int rear = (s1[i - 1] == s2[j - 1]) ? 0 : int(s1[i - 1] + s2[j - 1]);
              if (s1[i - 1] == s2[j - 1]) {
                  dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + rear);
              }
          }
      }

      return dp[size1][size2];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int dis = solu.minDistance("horse", "ros");
  LOG(INFO) << "ret: " << dis;
  return 0;
}
