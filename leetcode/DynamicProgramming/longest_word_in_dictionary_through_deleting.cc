#include <limits.h>
#include <algorithm>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::string;
using std::min;

// Problem:
// https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/

class Solution {
 public:
  static bool cmp(string &a, string &b) {
    if (a.size() == b.size()) return a < b;
    return a.size() > b.size();
  }
  string findLongestWord(string s, vector<string> &dictionary) {
    std::sort(dictionary.begin(), dictionary.end(), cmp);
    int len = s.size();
    for (auto &c : dictionary) {
      int left = 0, right = 0;
      int lenc = c.size();
      for (; left < len && right < lenc; left++) {
        if (s[left] == c[right]) {
          right++;
        }
      }
      if (right == lenc) return c;
    }
    return "";
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string s("abpcplea");
  vector<string> dictionary({"ale", "apple", "monkey", "plea"});
  string ret = solu.findLongestWord(s, dictionary);
  LOG(INFO) << ret;
  return 0;
}
