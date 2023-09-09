#include <cstdlib>
#include <random>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/split-a-string-in-balanced-strings/

class Solution {
 public:
  int balancedStringSplit(string s) {
    int count_l = 0;
    int count_r = 0;
    int p_l = 0;
    int p_r = 0;
    int ret = 0;
    while (p_l < s.size() && p_r < s.size()) {
      if (s[p_l] == 'L') count_l += 1;
      if (s[p_r] == 'R') count_r += 1;
      p_l += 1;
      p_r += 1;
      if (count_l == count_r) {
        ret += 1;
        count_l = 0;
        count_r = 0;
      }
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.balancedStringSplit("RLRRLLRLRL");
  LOG(INFO) << "ret : " << ret;
  return 0;
}
