#include <limits.h>
#include <algorithm>
#include <deque>
#include <stack>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/simplify-path/

class Solution {
 public:
  string simplifyPath(string path) {
    auto split = [](const string& s, char delim) -> vector<string> {
      vector<string> ans;
      string cur;
      for (char ch : s) {
        if (ch == delim) {
          ans.push_back(move(cur));
          cur.clear();
        } else {
          cur += ch;
        }
      }
      ans.push_back(move(cur));
      return ans;
    };

    vector<string> names = split(path, '/');
    vector<string> stk;
    for (string& name : names) {
      if (name == "..") {
        if (!stk.empty()) {
          stk.pop_back();
        }
      } else if (!name.empty() && name != ".") {
        stk.push_back(move(name));
      }
    }
    string ans;
    if (stk.empty()) {
      ans = "/";
    } else {
      for (string& name : stk) {
        ans += "/" + move(name);
      }
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  auto ret = solu.simplifyPath("/a/./b/d/../../c/");
  LOG(INFO) << ret;
  return 0;
}
