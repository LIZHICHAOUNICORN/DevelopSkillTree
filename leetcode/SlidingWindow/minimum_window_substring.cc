#include <string>
#include <vector>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problems: https://leetcode-cn.com/problems/minimum-window-substring/
// Solutions:
// https://leetcode-cn.com/problems/minimum-window-substring/solution/leetcode-76-zui-xiao-fu-gai-zi-chuan-cja-lmqz/

class Solution {
 public:
  string minWindow(string s, string t) {
    // hs哈希表维护的是s字符串中滑动窗口中各个字符出现多少次，ht哈希表维护的是t字符串各个字符出现多少次
    unordered_map<char, int> hs, ht;
    for (auto c : t) ht[c]++;

    string res;
    // cnt维护的是s字符串[j,i]区间中满足t字符串的元素的个数，记录相对应字符的总数
    int cnt = 0;
    for (int i = 0, j = 0; i < s.size(); i++) {
      hs[s[i]]++;
      // 对于新加入的字符s[i],如果hs[s[i]] <=
      // ht[s[i]]，说明当前新加入的字符s[i]是必需的，且还未到达字符串t所要求的数量
      if (hs[s[i]] <= ht[s[i]]) cnt++;

      // hs哈希表中s[j]的数量多于ht哈希表中s[j]的数量，此时我们就需要向右收缩滑动窗口
      while (hs[s[j]] > ht[s[j]]) hs[s[j++]]--;
      // 当cnt == t.size时，说明此时滑动窗口包含符串 t 的全部字符
      if (cnt == t.size()) {
        if (res.empty() || i - j + 1 < res.size()) res = s.substr(j, i - j + 1);
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string ret = solu.minWindow("ADOBECODEBANC", "ABC");

  LOG(INFO) << ret;
  return 0;
}
