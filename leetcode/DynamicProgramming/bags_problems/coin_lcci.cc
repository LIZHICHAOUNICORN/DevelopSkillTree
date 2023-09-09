#include <algorithm>
#include <climits>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

/*
 * Problems: https://leetcode-cn.com/problems/coin-lcci/
 */

// version 1, 暴力法
class Solution {
 private:
  int cnt = 0;
  vector<int> coins;

  void dfs(int total, int cur, int index) {
    if (cur == total) {
      cnt += 1;
      return;
    }

    for (int i = index; i < coins.size(); ++i) {
      if (cur + coins[i] > total) break;
      int key = cur + coins[i];
      dfs(total, key, i);
    }
  }

 public:
  Solution() : coins({1, 5, 10, 25}) {}
  int waysToChange(int n) {
    cnt = 0;
    dfs(n, 0, 0);
    return cnt % 1000000007;
  }
};

class Solution1 {
 private:
  static constexpr int mod = 1000000007;
  static constexpr int coins[4] = {25, 10, 5, 1};

 public:
  int waysToChange(int n) {
    vector<int> f(n + 1);
    f[0] = 1;
    for (int c = 0; c < 4; ++c) {
      int coin = coins[c];
      for (int i = coin; i <= n; ++i) {
        f[i] = (f[i] + f[i - coin]) % mod;
      }
    }
    return f[n];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  int amount = 90;

  Solution solu;
  int ret = solu.waysToChange(amount);
  LOG(INFO) << ret;

  return 0;
}
