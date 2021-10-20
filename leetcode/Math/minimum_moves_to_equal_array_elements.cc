#include <algorithm>
#include <climits>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements/

class Solution {
 public:
  int minMoves(vector<int>& nums) {
    int minNum = *min_element(nums.begin(), nums.end());
    int res = 0;
    for (int num : nums) {
      res += num - minNum;
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums({1, 2, 3});

  Solution solu;
  int ret = solu.minMoves(nums);
  LOG(INFO) << ret;

  return 0;
}
