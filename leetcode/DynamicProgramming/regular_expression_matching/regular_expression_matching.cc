#include <algorithm>
#include <climits>
#include <map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem:
// https://leetcode-cn.com/problhttps://leetcode-cn.com/problems/regular-expression-matching/
// Solutions:
// https://leetcode-cn.com/problems/regular-expression-matching/solution/qin-huai-gu-dao-zheng-ze-biao-da-shi-pi-rnl7g/

using namespace std;

class Solution {
 public:
  bool dfs(const string& s, const string& p, int s_index, int p_index) {
    if (p_index == p.size() && s_index == s.size()) return true;

    if (p_index + 1 < p.size() && p[p_index + 1] == '*') {
      while (s_index <= s.size()) {
        if (dfs(s, p, s_index, p_index + 2)) return true;
        if (p[p_index] == '.' || s[s_index] == p[p_index])
          ++s_index;
        else
          return false;
      }
      return false;
    } else {
      if (s_index == s.size()) return false;
      if (p[p_index] == '.' || s[s_index] == p[p_index])
        return dfs(s, p, s_index + 1, p_index + 1);
      else
        return false;
    }
  }
  bool isMatch(string s, string p) { return dfs(s, p, 0, 0); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  auto ret = solu.isMatch("abb", "a*");

  LOG(INFO) << ret;
  return 0;
}
