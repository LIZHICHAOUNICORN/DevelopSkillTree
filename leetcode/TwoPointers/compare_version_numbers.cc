#include <vector>
#include <string>
#include <iostream>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using std::vector;
using std::string;

// Problem: https://leetcode-cn.com/problems/compare-version-numbers/

class Solution {
 public:
  int compareVersion(string version1, string version2) {
    int n = version1.length(), m = version2.length();
    int i = 0, j = 0;
    while (i < n || j < m) {
      int x = 0;
      for (; i < n && version1[i] != '.'; ++i) {
          x = x * 10 + version1[i] - '0';
      }
      ++i; // 跳过点号
      int y = 0;
      for (; j < m && version2[j] != '.'; ++j) {
          y = y * 10 + version2[j] - '0';
      }
      ++j; // 跳过点号
      if (x != y) {
          return x > y ? 1 : -1;
      }
    }
    return 0;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.compareVersion("1.001", "1.1");
  LOG(INFO) << "ret " << ret;
  return 0;
}
