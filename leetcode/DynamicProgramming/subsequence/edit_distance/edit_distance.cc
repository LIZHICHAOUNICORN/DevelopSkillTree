#include <vector>
#include <limits.h>
#include <string>
#include <algorithm>

#include <glog/logging.h>
#include <gflags/gflags.h>

using std::vector;
using std::string;
using std::min;

// Problem: https://leetcode-cn.com/problems/edit-distance/

class Solution {
 public:
  int minDistance(string word1, string word2) {
      int n = word1.size(), m = word2.size();
      vector <vector<int>> dp(n + 1, vector<int>(m + 1));
      for(int i = 1; i <= n; i++) dp[i][0] = i;
      for(int i = 1; i <= m; i++) dp[0][i] = i;
      for(int i = 1; i <= n; i++) {
          for(int j = 1; j <= m; j++) {
              if(word1[i - 1] == word2[j - 1]) {
                  dp[i][j] = dp[i - 1][j - 1];
              }
              else {
                  dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
              }
          }
      }
      return dp[n][m];
  }
};

class Solution1 {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector <int> dp(m + 1);
        for(int i = 1; i <= m; i++) dp[i] = i;      // 初始化

        for(int i = 1; i <= n; i++) {
            int p = dp[0];  // dp[i - 1][j - 1]
            dp[0] = i;
            for(int j = 1; j <= m; j++) {
                int q = dp[j - 1];    // dp[i][j - 1]
                int r = dp[j];   // dp[i - 1][j]
                if(word1[i - 1] == word2[j - 1]) dp[j] = p;
                else dp[j] = min(p, min(q, r)) + 1;
                p = r;      // 更新 p
            }
        }
        return dp[m];   
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
