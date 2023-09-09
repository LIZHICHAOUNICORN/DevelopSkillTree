#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/distinct-subsequences/
// Solutions:
// https://leetcode-cn.com/problems/distinct-subsequences/solution/c-dfs-ji-yi-hua-sou-suo-dong-tai-gui-hua-m6e9/

using std::vector;
using std::string;

// 暴力搜索
class Solution {
 public:
  int dfs(string s, int index, string t, int cur) {
    // 遍历t，走到最终结束
    if (cur == t.size()) return 1;

    // 遍历s，走到最终，但目前t还没有，所以没有匹配成功
    if (index == s.size()) return 0;

    // 如果当前字符相等, 那么t可选择匹配当前字符，t也可以选择不匹配当前字符.
    if (s[index] == t[cur]) {
      return dfs(s, index + 1, t, cur + 1) + dfs(s, index + 1, t, cur);
    } else {
      // 因为不相等，所以，一定不匹配当前字符。
      return dfs(s, index + 1, t, cur);
    }
  }

  int numDistinct(string s, string t) { return dfs(s, 0, t, 0); }
};

// 加cache
class Solution1 {
 public:
  vector<vector<int>> arr;
  int dfs(string s, int index, string t, int cur) {
    // 遍历t，走到最终结束
    if (cur == t.size()) return 1;

    // 遍历s，走到最终，但目前t还没有，所以没有匹配成功
    if (index == s.size()) return 0;

    if (arr[cur][index] != -1) return arr[cur][index];

    if (s[index] == t[cur]) {
      arr[cur][index] =
          dfs(s, index + 1, t, cur + 1) + dfs(s, index + 1, t, cur);
    } else {
      arr[cur][index] = dfs(s, index + 1, t, cur);
    }

    return arr[cur][index];
  }

  int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    arr = vector<vector<int>>(m, vector<int>(n, -1));
    return dfs(s, 0, t, 0);
  }
};

class Solution2 {
 public:
  int numDistinct(string s, string t) {
    vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1));
    for (int i = 0; i < s.size(); i++) dp[i][0] = 1;
    for (int j = 1; j < t.size(); j++) dp[0][j] = 0;
    for (int i = 1; i <= s.size(); i++) {
      for (int j = 1; j <= t.size(); j++) {
        if (s[i - 1] == t[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }
    return dp[s.size()][t.size()];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string s("rabbbit");
  string t("rabbit");

  Solution solu;
  int ret = solu.numDistinct(s, t);

  LOG(INFO) << ret;
  return 0;
}
