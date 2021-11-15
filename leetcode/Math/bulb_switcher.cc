#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/bulb-switcher/

// 暴力解法
class Solution {
 public:
  int bulbSwitch(int n) {
    if (n <= 1) return n;
    vector<int> switchers(n, 1);
    for (int i = 2; i <= n; ++i) {
      for (int j = i - 1; j < n; j = j + i) {
        switchers[j] = switchers[j] == 1 ? 0 : 1;
      }
    }

    int ret = std::accumulate(switchers.begin(), switchers.end(), 0);
    return ret;
  }
};

class Solution1 {
 public:
  int bulbSwitch(int n) { return sqrt(n + 0.5); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.bulbSwitch(128);
  LOG(INFO) << ret;

  return 0;
}
