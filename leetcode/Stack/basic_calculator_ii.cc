#include <stack>
#include <string>
#include <unordered_map>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problems: https://leetcode-cn.com/problems/basic-calculator-ii/

class Solution {
 public:
  int calculate(string s) {
    vector<int> stk;
    char preSign = '+';
    int num = 0;
    int n = s.length();
    for (int i = 0; i < n; ++i) {
      if (isdigit(s[i])) {
        num = num * 10 + int(s[i] - '0');
      }
      if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1) {
        switch (preSign) {
          case '+':
            stk.push_back(num);
            break;
          case '-':
            stk.push_back(-num);
            break;
          case '*':
            stk.back() *= num;
            break;
          default:
            stk.back() /= num;
        }
        preSign = s[i];
        num = 0;
      }
    }
    return accumulate(stk.begin(), stk.end(), 0);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  string s("3+2*2");

  Solution solu;
  int ret = solu.calculate(s);
  LOG(INFO) << ret;

  return 0;
}
