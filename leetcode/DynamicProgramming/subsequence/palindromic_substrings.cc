#include <algorithm>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/palindromic-substrings/
// Solution:
// https://leetcode-cn.com/problems/palindromic-substrings/solution/dai-ma-sui-xiang-lu-dai-ni-xue-tou-dpzi-vidge/

using std::vector;
using std::string;
using std::max;

// 暴力
class Solution {
 private:
  bool isPalindromic(const string& s) {
    if (s.size() == 1) return true;
    for (int i = 0, j = s.size() - 1; i <= j; ++i, --j) {
      if (s[i] != s[j]) return false;
    }
    return true;
  }

 public:
  int countSubstrings(string s) {
    int ret = 0;
    for (int i = 0; i < s.size(); ++i) {
      for (int j = i + 1; j <= s.size(); ++j) {
        const string& sub = s.substr(i, j - i);
        if (isPalindromic(sub)) ret += 1;
      }
    }
    return ret;
  }
};

// DP
// s[i] == s[j] :
//  dp[i][j] = true (j - i <= 1, 由于定义状态，dp[i][j]是s[i, j], j 一定大于i)
//  dp[i][j] = dp[i+1][j-1] (j -i > 1)
class Solution1 {
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

// DP : 情况一二和情况三合并
class Solution2 {
 public:
  int countSubstrings(string s) {
    vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
    int result = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
      for (int j = i; j < s.size(); j++) {
        if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
          result++;
          dp[i][j] = true;
        }
      }
    }
    return result;
  }
};

// 双指针
class Solution3 {
 public:
  int countSubstrings(string s) {
    int result = 0;
    for (int i = 0; i < s.size(); i++) {
      result += extend(s, i, i, s.size());      // 以i为中心
      result += extend(s, i, i + 1, s.size());  // 以i和i+1为中心
    }
    return result;
  }
  int extend(const string& s, int i, int j, int n) {
    int res = 0;
    while (i >= 0 && j < n && s[i] == s[j]) {
      i--;
      j++;
      res++;
    }
    return res;
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
