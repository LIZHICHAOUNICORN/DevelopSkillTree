#include <vector>
#include <limits.h>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::min;
using std::max;

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];
    int min_neg = 0;
    int max_pos = 0;
    int res = INT_MIN;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        min_neg = max_pos = 0;
      } else if (nums[i] > 0) {
        max_pos = max(max_pos * nums[i], nums[i]);
        min_neg = min_neg * nums[i];
      } else {
        int t = max_pos;
        max_pos = min_neg * nums[i];
        min_neg = min(t * nums[i], nums[i]);
      }
      res = max(res, max_pos);
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
  int ret = solu.maxProduct(nums);
  LOG(INFO) << ret;
  return 0;
}
