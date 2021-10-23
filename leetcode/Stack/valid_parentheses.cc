#include <stack>
#include <string>
#include <unordered_map>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problems: https://leetcode-cn.com/problems/valid-parentheses/

class Solution {
 public:
  bool isValid(string s) {
    int n = s.size();
    if (n % 2 == 1) {
      return false;
    }

    unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
    stack<char> stk;
    for (char ch : s) {
      if (pairs.count(ch)) {
        if (stk.empty() || stk.top() != pairs[ch]) {
          return false;
        }
        stk.pop();
      } else {
        stk.push(ch);
      }
    }
    return stk.empty();
  }
};

class Solution1 {
 public:
  bool isValid(string s) {
    if (s.empty()) return true;
    stack<char> cont;
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
      if (*it == '{' || *it == '(' || *it == '[') {
        cont.push(*it);
        continue;
      } else if (*it == '}' || *it == ')' || *it == ']') {
        if (cont.empty()) return false;
        char left = cont.top();
        cont.pop();
        if (((*it == '}') && (left == '{')) ||
            ((*it == ')') && (left == '(')) ||
            ((*it == ']') && (left == '['))) {
          continue;
        }
        return false;
      }
    }
    if (cont.empty()) return true;
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  string s("{[]}");
  Solution solu;
  bool ret = solu.isValid(s);
  LOG(INFO) << ret;

  return 0;
}
