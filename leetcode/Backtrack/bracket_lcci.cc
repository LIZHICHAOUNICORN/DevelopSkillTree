#include <functional>
#include <stack>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::stack;
using std::string;
using std::function;

// Problem: https://leetcode-cn.com/problems/decode-string/

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    string s;
    s.push_back('(');
    dfs(n, 1, 0, s);
    return res;
  }

 private:
  vector<string> res;
  void dfs(int n, int l, int r, string& s) {
    if (l > n || l < r) return;
    if (l == n && r == n) {
      res.push_back(s);
      return;
    }
    if (l < n) {
      s.push_back('(');
      dfs(n, l + 1, r, s);
      s.pop_back();
    }
    if (l > r) {
      s.push_back(')');
      dfs(n, l, r + 1, s);
      s.pop_back();
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  vector<string> ret = solu.generateParenthesis(3);
  LOG(INFO) << ret.back();
  return 0;
}
