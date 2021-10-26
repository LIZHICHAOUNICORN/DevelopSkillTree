#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::string;

// Problem:
// https://leetcode-cn.com/problems/valid-palindrome/

class Solution {
 public:
  bool isPalindrome(string s) {
    int n = s.size();
    int left = 0, right = n - 1;
    while (left < right) {
      while (left < right && !isalnum(s[left])) {
        ++left;
      }
      while (left < right && !isalnum(s[right])) {
        --right;
      }
      if (left < right) {
        if (tolower(s[left]) != tolower(s[right])) {
          return false;
        }
        ++left;
        --right;
      }
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string s("A man, a plan, a canal: Panama");

  Solution solu;
  bool ret = solu.isPalindrome(s);
  LOG(INFO) << ret;

  return 0;
}
