#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problems: https://leetcode-cn.com/problems/word-break
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;

// DFS
class Solution {
  vector<int> ans;

 public:
  void dfs(int num, int& n) {
    if (num > n) return;
    ans.push_back(num);
    for (int i = 0; i <= 9; ++i) dfs(num * 10 + i, n);
  }

  vector<int> lexicalOrder(int n) {
    for (int i = 1; i <= 9; ++i) dfs(i, n);
    return ans;
  }
};

class Solution1 {
 public:
  vector<int> lexicalOrder(int n) {
    vector<string> strs;
    for (int i(1); i <= n; i++) {
      strs.push_back(to_string(i));
    }
    sort(strs.begin(), strs.end());
    vector<int> res;
    for (int j(0); j < n; j++) {
      res.push_back(stoi(strs[j]));
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  auto ret = solu.lexicalOrder(100);
  return 0;
}
