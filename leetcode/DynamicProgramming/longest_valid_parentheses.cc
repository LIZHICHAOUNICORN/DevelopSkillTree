#include <iostream>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

ass Solution{
  public : int longestValidParentheses(string s){int maxans = 0, n = s.length();
vector<int> dp(n, 0);
for (int i = 1; i < n; i++) {
  if (s[i] == ')') {
    if (s[i - 1] == '(') {
      dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
    } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
      dp[i] =
          dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
    }
    maxans = max(maxans, dp[i]);
  }
}
return maxans;
}
}
;

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string s(")()())");
  int ret = solu.longestValidParentheses(s);
  LOG(INFO) << ret;
  return 0;
}
