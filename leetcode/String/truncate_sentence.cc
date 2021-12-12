#include <string>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/truncate-sentence/

class Solution {
 public:
  string truncateSentence(string s, int k) {
    int n = s.size();
    int end = 0, count = 0;
    for (int i = 1; i <= n; i++) {
      if (i == n || s[i] == ' ') {
        count++;
        if (count == k) {
          end = i;
          break;
        }
      }
    }
    return s.substr(0, end);
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string s("chopper is not a tanuki");
  int k = 4;
  string ret = solu.truncateSentence(s, k);
  LOG(INFO) << ret;
  return 0;
}
