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

DEFINE_string(test_case, "3[a2[c]]", "test case");

// Problem: https://leetcode-cn.com/problems/decode-string/

// Stack
class Solution {
 public:
  string decodeString(string s) {
    stack<int> numStack;
    stack<string> resStack;
    int num = 0;
    string res;
    for (int i = 0; i < s.size(); i++) {
      // 字母时候
      if (isalpha(s[i])) {
        res.push_back(s[i]);
      // 数字
      } else if (isdigit(s[i])) {
        num = num * 10 + s[i] - '0';
      // 入栈时刻
      } else if (s[i] == '[') {
        resStack.push(res);
        res = "";
        numStack.push(num);
        num = 0;
      } else {
        for (int j = 0; j < numStack.top(); j++) {
          resStack.top() += res;
        }
        numStack.pop();
        res = resStack.top();
        resStack.pop();
      }
    }
    return res;
  }
};


// recurrent
class Solution1 {
 public:
  string decodeString(string s) {
    int num = 0;
    string res;
    for (int i = 0; i < s.size(); i++) {
      if (isalpha(s[i])) {
        res.push_back(s[i]);
      } else if (isdigit(s[i])) {
        num = num * 10 + s[i] - '0';
      } else if (s[i] == '[') {
        int cnt = 0;
        i++;
        string innerS;
        while (s[i] != ']' || cnt != 0) {
          if (s[i] == '[')
            cnt++;
          else if (s[i] == ']')
            cnt--;
          innerS.push_back(s[i]);
          i++;
        }
        string innerRes = decodeString(innerS);
        while (num > 0) {
          res += innerRes;
          num--;
        }
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string ret = solu.decodeString(FLAGS_test_case);
  LOG(INFO) << ret;
  return 0;
}
