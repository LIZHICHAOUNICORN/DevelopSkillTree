#include <algorithm>
#include <climits>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/palindrome-partitioning-ii/

using namespace std;

class Solution {
 public:
  int minCut(string s) {
    int n = s.size();
    vector<vector<int>> g(n, vector<int>(n, 1));

    for (int i = n - 1; i >= 0; --i) {
      for (int j = i + 1; j < n; ++j) {
        g[i][j] = (s[i] == s[j]) && g[i + 1][j - 1];
      }
    }

    vector<int> f(n, INT_MAX);
    for (int i = 0; i < n; ++i) {
      if (g[0][i]) {
        f[i] = 0;
      } else {
        for (int j = 0; j < i; ++j) {
          if (g[j + 1][i]) {
            f[i] = min(f[i], f[j] + 1);
          }
        }
      }
    }

    return f[n - 1];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.minCut("aabcc");
  LOG(INFO) << ret;
  return 0;
}
