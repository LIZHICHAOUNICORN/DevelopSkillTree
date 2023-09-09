#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/short-encoding-of-words/
// Solutions:
// https://leetcode-cn.com/problems/camelcase-matching/solution/que-ding-you-xian-zhuang-tai-zi-dong-ji-d5z1j/

using namespace std;
class Solution {
 public:
  vector<bool> camelMatch(vector<string> &queries, string pattern) {
    vector<bool> res;
    for (const auto &q : queries) {
      if (canMatch(q, pattern)) {
        res.push_back(true);
      } else {
        res.push_back(false);
      }
    }

    return res;
  }

 private:
  bool canMatch(const string &q, const string &pattern) {
    int i = 0;
    int j = 0;
    int M = q.size();
    int N = pattern.size();
    while (i < M) {
      if (j < N && q[i] == pattern[j]) {
        i++;
        j++;
      } else if (isupper(q[i])) {
        return false;
      } else {
        i++;
      }
    }

    return i == M && j == N;
  }
};

class Solution {
 public:
  int nextStatus(string &pattern, int status, char in) {
    if (status == -2)  // 状态是-2，则不管什么输入，状态还是-2
      return -2;
    if (status ==
        pattern.size() -
            1)  // 如果到了最后一个状态，如果是大写字母，那么匹配失败，转移到-2，否则状态不转移
    {
      if (in >= 'A' && in <= 'Z')
        return -2;
      else
        return status;
    }

    if (pattern[status + 1] ==
        in)  // 如果输入正好是下一个字符，那么状态转移到下一个字符上
    {
      return status + 1;
    } else  // 如果不是，并且还是大写字母，那么匹配失败，如果是小写字母状态不转移
    {
      if (in >= 'A' && in <= 'Z')
        return -2;
      else
        return status;
    }
  }
  bool check(string &query, string &pattern) {
    int status = -1;      // 初始状态
    for (char t : query)  // 依次把字符输入到自动机
    {
      status = nextStatus(pattern, status, t);  // 获取下一个状态
      if (status == -2)  // 如果遇见状态是-2，则直接返回false
        return false;
    }

    return status == pattern.size() - 1;  // 判断是否是接受状态
  }
  vector<bool> camelMatch(vector<string> &queries, string pattern) {
    vector<bool> ans;

    for (string &q : queries) {
      ans.push_back(check(q, pattern));
    }

    return ans;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> wordDict(
      {"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"});
  string pattern({"FB"});

  Solution solu;
  auto ret = solu.camelMatch(wordDict, pattern);
  return 0;
}
