#include <algorithm>
#include <climits>
#include <vector>
#include <map>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/perfect-squares/
// Solution:
// https://leetcode-cn.com/problems/k-inverse-pairs-array/solution/tong-ge-lai-shua-ti-la-yi-ti-wu-jie-bao-ej4ym/

using namespace std;

class Solution1 {
 private:
  int dfs(int n, int k) {
    // stop
    if (k > n * (n - 1) / 2) return 0;

    if (n == 1) {
      return k == 0 ? 1 : 0;
    }

    int ret = 0;
    for (int i = std::max(0, k - n + 1); i <= k; ++i) {
      ret += dfs(n - 1, i);
    }
    return ret;
  }

 public:
  const static int mod = 1000000007;
  int kInversePairs(int n, int k) {
    // stop
    if (k > n * (n - 1) / 2) return 0;

    if (n == 1) {
      return k == 0 ? 1 : 0;
    }

    int ret = 0;
    ret += dfs(n, k);

    return ret % mod;
  }
};

// 第二版：  bfs 暴力版，加cache.

class Solution2 {
 private:
  int dfs(int n, int k) {
    // stop
    if (k > n * (n - 1) / 2) {
      return 0;
    }
    if (n == 1) {
      return k == 0 ? 1 : 0;
    }

    pair<int, int>&& key = std::make_pair(n, k);
    if (cache.count(key) > 0) {
      return cache[key];
    }

    long ret = 0;
    for (int i = std::max(0, k - n + 1); i <= k; ++i) {
      ret += dfs(n - 1, i);
    }

    cache[key] = (ret % MOD);

    return (ret % MOD);
  }

 public:
  const static int MOD = 1000000007;
  map<pair<int, int>, int> cache;
  int kInversePairs(int n, int k) {
    // prune
    if (k > n * (n - 1) / 2) return 0;
    if (n == 1) {
      return k == 0 ? 1 : 0;
    }

    long ret = 0;
    ret += dfs(n, k);

    return static_cast<int>(ret % MOD);
  }
};
// 第三版： 原始动态规划

class Solution3 {
 public:
  static const int MOD = 1000000007;
  int kInversePairs(int n, int k) {
    int ret = 0;
    if (k > n * (n - 1) / 2) return ret;
    if (n == 1) {
      return k == 0 ? 1 : ret;
    }

    vector<vector<long>> dp(n + 1, vector<long>(k + 1, 0));
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j <= std::min(k, i * (i - 1) / 2); j++) {
        for (int x = std::max(0, j - i + 1); x <= j; x++) {
          dp[i][j] = (dp[i][j] + dp[i - 1][x]) % MOD;
        }
      }
    }
    return dp[n][k];
  }
};

// 第四版： 动态规划，优化计算

class Solution4 {
 public:
  static const int MOD = 1000000007;
  int kInversePairs(int n, int k) {
    int ret = 0;
    if (k > n * (n - 1) / 2) return ret;
    if (n == 1) {
      return k == 0 ? 1 : ret;
    }

    vector<vector<long>> dp(n + 1, vector<long>(k + 1, 0));
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j <= std::min(k, i * (i - 1) / 2); j++) {
        dp[i][j] = ((j >= 1 ? dp[i][j - 1] : 0) + dp[i - 1][j] -
                    (j >= i ? dp[i - 1][j - i] : 0) + MOD) %
                   MOD;
      }
    }
    return dp[n][k];
  }
};

// 第五版， 动态规划，优化计算，状态压缩

class Solution {
 public:
  static const int MOD = 1000000007;
  int kInversePairs(int n, int k) {
    int ret = 0;
    if (k > n * (n - 1) / 2) return ret;
    if (n == 1) {
      return k == 0 ? 1 : ret;
    }

    vector<vector<long>> dp(2, vector<long>(k + 1, 0));
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j <= std::min(k, i * (i - 1) / 2); j++) {
        dp[i & 1][j] = ((j >= 1 ? dp[i & 1][j - 1] : 0) + dp[(i - 1) & 1][j] -
                        (j >= i ? dp[(i - 1) & 1][j - i] : 0) + MOD) %
                       MOD;
      }
    }
    return dp[n & 1][k];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.kInversePairs(10, 3);

  LOG(INFO) << ret;
  return 0;
}
