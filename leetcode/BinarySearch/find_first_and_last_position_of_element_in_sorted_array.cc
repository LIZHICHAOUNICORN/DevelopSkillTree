#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;

class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;
    int mid = 0;
    while (l <= r) {
      mid = (l + r) / 2;
      if (nums[mid] == target) break;
      if (target > nums[mid]) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    // 边界条件
    if (nums.size() == 0 || nums[mid] != target) return {-1, -1};

    int start = mid;
    int last = mid;
    while (start >= 0 && nums[start] == target) {
      start -= 1;
    }
    while (last < nums.size() && nums[last] == target) {
      last += 1;
    }
    return {start + 1, last - 1};
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums({5, 7, 7, 8, 8, 10});
  solu.searchRange(nums, 8);
  return 0;
}
