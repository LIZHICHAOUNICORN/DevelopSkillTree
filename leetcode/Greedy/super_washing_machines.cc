#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/super-washing-machines/
// Solution:
// https://leetcode-cn.com/problems/super-washing-machines/solution/517-chao-ji-xi-yi-ji-zui-da-ci-shu-jiu-s-cqts/

class Solution {
 public:
  int findMinMoves(vector<int>& machines) {
    int tot = accumulate(machines.begin(), machines.end(), 0);
    int n = machines.size();
    if (tot % n) {
      return -1;
    }
    int avg = tot / n;
    int ans = 0, sum = 0;
    for (int num : machines) {
      // 当前达到平衡需要移动的次数
      num -= avg;
      // 前i个需要移动次数
      sum += num;
      ans = max(ans, max(abs(sum), num));
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> machines({3, 0, 1, 4});
  Solution solu;
  int ret = solu.findMinMoves(machines);

  LOG(INFO) << "result: " << ret;
  return 0;
}
