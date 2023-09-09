#include <limits.h>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::string;
using std::min;
using namespace std;

// Problem:
// https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/

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

// 最长公共子序列变种
class Solution1 {
 public:
  int minimumDeleteSum(string s1, string s2) {
    int sum = 0;
    int m = s1.size();
    int n = s2.size();
    sum = accumulate(s1.begin(), s1.end(), 0);
    sum += accumulate(s2.begin(), s2.end(), 0);
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (s1[i - 1] == s2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + static_cast<int>(s1[i - 1]);
        } else {
          dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
      }
    }
    return sum - 2 * dp[m][n];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int dis = solu.minimumDeleteSum("horse", "ros");
  LOG(INFO) << "ret: " << dis;
  return 0;
}
