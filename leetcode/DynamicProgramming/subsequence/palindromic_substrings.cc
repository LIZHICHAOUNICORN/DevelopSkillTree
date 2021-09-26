#include <algorithm>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/palindromic-substrings/
// Solution:
// https://leetcode-cn.com/problems/palindromic-substrings/solution/dai-ma-sui-xiang-lu-dai-ni-xue-tou-dpzi-vidge/

using std::vector;
using std::string;
using std::max;

class Solution {
 public:
  int countSubstrings(string s) {
    vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
    int result = 0;
    for (int i = s.size() - 1; i >= 0; i--) {  // 注意遍历顺序
      for (int j = i; j < s.size(); j++) {
        if (s[i] == s[j]) {
          if (j - i <= 1) {  // 情况一 和 情况二
            result++;
            dp[i][j] = true;
          } else if (dp[i + 1][j - 1]) {  // 情况三
            result++;
            dp[i][j] = true;
          }
        }
      }
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.countSubstrings("aaa");
  LOG(INFO) << ret;
  return 0;
}
