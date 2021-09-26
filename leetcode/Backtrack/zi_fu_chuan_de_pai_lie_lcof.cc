#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::set;

class Solution {
 public:
  vector<string> permutation(string s) {
    backtrack(s, 0);
    return res;
  }

 private:
  vector<string> res;
  void backtrack(string& s, int x) {
    if (x == s.size() - 1) {
      res.push_back(s);  // 添加排列方案
      return;
    }
    set<int> st;
    for (int i = x; i < s.size(); i++) {
      if (st.find(s[i]) != st.end()) continue;  // 重复，因此剪枝
      st.insert(s[i]);
      std::swap(s[i], s[x]);  // 交换，将 s[i] 固定在第 x 位
      backtrack(s, x + 1);    // 开启固定第 x + 1 位字符
      std::swap(s[i], s[x]);  // 恢复交换
    }
  }
};

class Solution1 {
 public:
  vector<string> rec;
  vector<int> vis;

  void backtrack(const string& s, int i, int n, string& perm) {
    if (i == n) {
      rec.push_back(perm);
      return;
    }
    for (int j = 0; j < n; j++) {
      if (vis[j] || (j > 0 && !vis[j - 1] && s[j - 1] == s[j])) {
        continue;
      }
      vis[j] = true;
      perm.push_back(s[j]);
      backtrack(s, i + 1, n, perm);
      perm.pop_back();
      vis[j] = false;
    }
  }

  vector<string> permutation(string s) {
    int n = s.size();
    vis.resize(n);
    std::sort(s.begin(), s.end());
    string perm;
    backtrack(s, 0, n, perm);
    return rec;
  }
};

int main(int argc, char* argv[]) {
  Solution solu;
  string s("abc");
  vector<string> ret = solu.permutation(s);
  for (auto i : ret) {
    std::cout << i << std::endl;
  }
  return 0;
}
