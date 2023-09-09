#include <map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/unique-paths/

using std::vector;

// recursive
// dp[m][n] = dp[m-1][n] + dp[m][n-1]
// when m = 0 or n = 0; dp[m][n] =1
// 深搜的深度：m+n-1
// 节点的深度：(2^(m+n-1))-1
class Solution {
 public:
  int uniquePaths(int m, int n) {
    vector<vector<int>> cache(m, vector<int>(n, 0));
    return helper(m - 1, n - 1, cache);
  }
  int helper(int m, int n, vector<vector<int>>& cache) {
    if (m < 0 || n < 0) return 0;
    if (m == 0 || n == 0) return 1;
    if (cache[m][n] > 0) return cache[m][n];
    cache[m][n] = helper(m - 1, n, cache) + helper(m, n - 1, cache);
    ;
    return cache[m][n];
  }
};

// Time: O(m * n)
// Space: O(m * n)
class Solution1 {
 public:
  int uniquePaths(int m, int n) {
    if (m == 0 || n == 0) {
      return 0;
    }
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 1;
    for (size_t i = 0; i < m; ++i) {
      dp[i][0] = 1;
    }
    for (size_t i = 0; i < n; ++i) {
      dp[0][i] = 1;
    }
    for (size_t i = 1; i < m; ++i) {
      for (size_t j = 1; j < n; ++j) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
    return dp[m - 1][n - 1];
  }
};

// 降维
class Solution2 {
 public:
  int uniquePaths(int m, int n) {
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
      dp[i] = 1;
    }
    for (int j = 1; j < m; j++) {
      for (int i = 1; i < n; i++) {
        dp[i] += dp[i - 1];
      }
    }
    return dp[n - 1];
  }
};

// 暴力+cache
class Solution3 {
 private:
  std::map<std::pair<int, int>, int> cache;

 public:
  int CountPath(int m, int n, int path) {
    // terminate
    if (m <= 1) return m;
    if (n <= 1) return n;

    // process current level
    std::pair<int, int> key = std::make_pair(m, n);
    if (cache.find(key) != cache.end()) {
      return cache[key];
    }
    cache[key] = CountPath(m - 1, n, path) + CountPath(m, n - 1, path);
    return cache[key];
  }
  int uniquePaths(int m, int n) {
    if (m <= 1) return m;
    if (n <= 1) return n;

    return CountPath(m - 1, n, 0) + CountPath(m, n - 1, 0);
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
