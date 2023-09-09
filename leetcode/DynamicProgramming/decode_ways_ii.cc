#include <algorithm>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::min;
using std::string;

class Solution {
 private:
  int MOD = 1000000007;
  int decodeOneChar(char c) {
    if (c == '*') {
      // * 可选 1~9 任意一个数解码
      return 9;
    }
    // 确定的数字与前一位的解码方案数保持一致
    return 1;
  }
  int decodeTwoChars(char c1, char c2) {
    // 解码 **
    if (c1 == '*' && c2 == '*') {
      return 15;
    }
    // 解码 *d
    if (c1 == '*') {
      // 如果当前位为 0~6，* 可选1和2
      if (c2 <= '6') {
        return 2;
      }
      // 如果当前位为 7~9，*只能选择1
      return 1;
    }
    // 解码 1*/2*
    if (c2 == '*') {
      // 如果前一位为1，则有 1~9 共9种选择
      if (c1 == '1') {
        return 9;
      }
      // 如果前一位为2，则有 1~6 共6种选择
      if (c1 == '2') {
        return 6;
      }
      // 如果前一位为 0 或 3~9，则不行
      return 0;
    }
    // 解码 dd
    // 两个字符的和是 10 ~ 26 才能够组合在一起，否则不行
    int twoSum = (c1 - '0') * 10 + (c2 - '0');
    if (twoSum >= 10 && twoSum <= 26) {
      return 1;
    }
    return 0;
  }

  long dfs(const string& s, int pos, vector<int>& dp) {
    // 结束条件：分割位置为字符末尾。
    if (pos == s.size()) {
      return 1;
    }
    // 结束条件：分割位置超出字符长度。
    if (pos > s.size()) {
      return 0;
    }
    // 结束条件：当前字符时 0；
    if (s[pos] == '0') return 0;
    // 如果cache中已经计算过，则直接返回结果。
    if (dp[pos] != -1) return dp[pos];

    long long one_sum = decodeOneChar(s[pos]) * dfs(s, pos + 1, dp);
    long long two_sum = 0;
    if (s.size() > pos + 1) {
      two_sum = decodeTwoChars(s[pos], s[pos + 1]) * dfs(s, pos + 2, dp);
    }
    dp[pos] = (one_sum + two_sum) % MOD;
    return dp[pos];
  }

 public:
  int numDecodings(string s) {
    // 单个字符解码
    if (s.size() == 1) {
      if (s[0] == '*') return 9;
      return s[0] == '0' ? 0 : 1;
    }
    // dp状态，cache
    vector<int> dp(s.size(), -1);
    return dfs(s, 0, dp);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.numDecodings("7*9*3*6*3*0*5*4*9*7*3*7*1*8*3*2*0*0*6*");
  LOG(INFO) << ret;
  return 0;
}
