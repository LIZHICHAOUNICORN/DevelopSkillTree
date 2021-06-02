#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

// recursive
// dp[m][n] = dp[m-1][n] + dp[m][n-1]
// when m = 0 or n = 0; dp[m][n] =1
class Solution {
 public:
  int uniquePaths(int m, int n){
    vector<vector<int>> cache(m,vector<int>(n,0));
    return helper(m-1, n-1, cache);
  }
  int helper(int m, int n, vector<vector<int>>& cache){
    if(m < 0 || n < 0) return 0;
    if(m == 0 || n == 0) return 1;
    if(cache[m][n] > 0) return cache[m][n];
    cache[m][n] =helper(m-1, n, cache) + helper(m, n-1, cache);;
    return cache[m][n];
  }
};

// loop
class Solution1 {
 public:
  int uniquePaths(int m, int n) {
    if (m == 0 || n == 0) {
      return 0;
    }
    vector<vector<int>> dp(m, vector<int>(n));
    dp[0][0] = 1;
    for (int i = 1; i < m; i++) {
      dp[i][0] = dp[i - 1][0];
    }
    for (int j = 1; j < n; j++) {
      dp[0][j] = dp[0][j - 1];
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
    return dp[m - 1][n - 1];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.uniquePaths(3, 3);
  LOG(INFO) << ret;
  return 0;
}
