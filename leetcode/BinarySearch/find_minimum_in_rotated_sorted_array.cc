#include <vector>
#include <assert.h>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::min;

class Solution {
 public:
  int findMin(vector<int>& nums) {

    assert(nums.size() > 0);
    if(nums.size() == 1)
        return nums[0];
    if(nums.size() == 2)
        return min(nums[0], nums[1]);

    int l = 0, r = nums.size() - 1;
    while(l < r) {
        int mid = l + (r - l) / 2;
        if(nums[l] <= nums[mid] && nums[mid] <= nums[r])
            return nums[l];

        if(nums[l] > nums[mid])
            l = l + 1, r = mid;
        else if(nums[r] < nums[mid])
            l = mid + 1;
        else
            assert(false);
    }
    return nums[l];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {3,4,5,1,2};
  int ret = solu.findMin(nums);
  LOG(INFO) << ret;
  return 0;
}
