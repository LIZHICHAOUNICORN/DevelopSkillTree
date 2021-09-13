#include <vector>
#include <limits.h>
#include <string>
#include <algorithm>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using std::vector;
using std::string;
using std::min;

// Problem: https://leetcode-cn.com/problems/edit-distance/

class Solution {
 public:
  int minDistance(string word1, string word2) {
      vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
      for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
      for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
      for (int i = 1; i <= word1.size(); i++) {
          for (int j = 1; j <= word2.size(); j++) {
              if (word1[i - 1] == word2[j - 1]) {
                  dp[i][j] = dp[i - 1][j - 1];
              } else {
                  dp[i][j] = min({dp[i - 1][j - 1] + 2, dp[i - 1][j] + 1, dp[i][j - 1] + 1});
              }
          }
      }
      return dp[word1.size()][word2.size()];
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
