#include <stack>
#include <vector>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using namespace std;

// Problems: https://leetcode-cn.com/problems/number-of-boomerangs/

class Solution {
 public:
  int numberOfBoomerangs(vector<vector<int>> &points) {
    int ans = 0;
    for (auto &p : points) {
      unordered_map<int, int> cnt;
      for (auto &q : points) {
        int dis = (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]);
        ++cnt[dis];
      }
      for (auto & [ _, m ] : cnt) {
        ans += m * (m - 1);
      }
    }
    return ans;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;

  return 0;
}
