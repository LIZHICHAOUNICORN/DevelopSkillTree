#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if ((nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid])) {
        lo = mid + 1;
      }
      else {
        hi = mid;
      }
    }
    return lo == hi && nums[lo] == target ? lo : -1;
  }
};


class Solution1 {
 public:
  int search(vector<int>& nums, int target) {
    int l = 0, r = nums.size() -1;

    while (l <= r) {
      int mid = (l + r) >> 1;
      if (target == nums[mid]) return mid;
      if (nums[l] <= nums[mid]) {
        if (target >= nums[l] && target < nums[mid]) {
          r = mid-1;
        }
        else {
          l = mid+1;
        }
      }
      else {
        if (target > nums[mid] && target <= nums[r]) {
          l = mid +1;
        } else {
          r = mid -1;
        }
      }
    }
    return -1;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {4,5,6,7,0,1,2};
  int ret = solu.search(nums, 0);
  LOG(INFO) << ret;
  return 0;
}
