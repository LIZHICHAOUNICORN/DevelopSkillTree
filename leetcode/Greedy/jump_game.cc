#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

// 自底向上的贪心算法
class Solution {
 public:
  bool canJump(vector<int>& nums) {
    if (nums.empty()) return true;
    if (nums.size() == 1 && nums[0] >= 1) return true;
    int pos = nums.size() - 1;
    for (int i = nums.size()-2; i >= 0; --i) {
      if (pos - nums[i] <= i) pos = i;
    }
    return pos == 0;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> g = {3,2,1,0,4};
  bool ret = solu.canJump(g);
  LOG(INFO) << ret;
  return 0;
}
