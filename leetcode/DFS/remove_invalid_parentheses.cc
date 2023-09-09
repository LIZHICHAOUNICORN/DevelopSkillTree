#include <algorithm>
#include <climits>
#include <unordered_set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/remove-invalid-parentheses/
// Solution:
// https://leetcode-cn.com/problems/remove-invalid-parentheses/solution/c-pu-tong-dfs16-mshe-jian-zhi-you-hua-hou-de-dfs0-/

using namespace std;

class Solution {
 public:
  unordered_set<string> ans;  //答案中可能会重复 需要去重 如(() 删除第一个(
  //或删除第二个( 都是() 这也提示了优化方法
  void dfs(string &s, int u, string res, int cnt, int l,
           int r) {  // cnt为当前左-右的值 l为需要删除的左括号数量 r为右
    // cout<<res<<endl;
    if (u == s.size()) {
      if (!cnt) ans.insert(res);
      return;
    }
    if (s[u] == '(') {  //在合法的条件下考虑删除
      dfs(s, u + 1, res + '(', cnt + 1, l, r);       //不删
      if (l > 0) dfs(s, u + 1, res, cnt, l - 1, r);  //删当前的左括号
    } else if (s[u] == ')') {  //在合法的条件下考虑删除
      if (cnt > 0) dfs(s, u + 1, res + ')', cnt - 1, l, r);  //不删
      if (r > 0) dfs(s, u + 1, res, cnt, l, r - 1);  //删当前的右括号
    } else
      dfs(s, u + 1, res + s[u], cnt, l, r);
  }
  vector<string> removeInvalidParentheses(string s) {
    int l = 0, r = 0;  // l为当前左括号-右括号的值 r为需要删掉的右括号的值
    for (auto v : s) {
      if (v == '(')
        l++;
      else if (v == ')') {
        if (l <= 0)
          r++;  //此时无效 右括号 必删
        else
          l--;  //右括号+1 则左-右的值需要--
      }
    }
    //此时的l为需要删除的左括号数量 r为需要删除的右括号数量
    dfs(s, 0, "", 0, l, r);
    vector<string> ret;
    for (auto v : ans) ret.push_back(v);
    return ret;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string s("()())()");
  Solution solu;
  auto ret = solu.removeInvalidParentheses(s);
  for (auto &r : ret) {
    LOG(INFO) << r;
  }
  return 0;
}
