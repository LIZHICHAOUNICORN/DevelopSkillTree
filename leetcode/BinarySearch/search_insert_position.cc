#include <vector>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using std::vector;
class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
      if (target < nums.front()) return 0;
      if (target > nums.back()) return nums.size();
      int l = 0;
      int r = nums.size() - 1;
      int mid = 0;
      while (l <= r) {
          mid = l + (r-l)/2;
          if (target == nums[mid]) return mid;
          if (target > nums[mid]) {
              l = mid + 1;
          } else if (target < nums[mid]) {
              r = mid - 1;
          }
      }
      return l;

  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums({5,7,8,10});
  solu.searchInsert(nums, 8);
  return 0;
}
