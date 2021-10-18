#include <string>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/count-and-say/

class Solution {
 public:
  string countAndSay(int n) {
    string prev = "1";
    for (int i = 2; i <= n; ++i) {
      string curr = "";
      int start = 0;
      int pos = 0;

      while (pos < prev.size()) {
        while (pos < prev.size() && prev[pos] == prev[start]) {
          pos++;
        }
        curr += to_string(pos - start) + prev[start];
        start = pos;
      }
      prev = curr;
    }

    return prev;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string ret = solu.countAndSay(15);
  LOG(INFO) << ret;
  return 0;
}
