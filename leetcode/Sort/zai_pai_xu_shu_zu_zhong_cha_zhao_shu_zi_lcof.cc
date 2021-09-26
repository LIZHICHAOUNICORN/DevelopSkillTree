#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int result = 0;
    for (auto it : nums) {
      if (it == target) {
        result += 1;
      }
    }
    return result;
  }
};

class Solution1 {
 public:
  int binarySearch(vector<int>& nums, int target, bool lower) {
    int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
    while (left <= right) {
      int mid = (left + right) / 2;
      if (nums[mid] > target || (lower && nums[mid] >= target)) {
        right = mid - 1;
        ans = mid;
      } else {
        left = mid + 1;
      }
    }
    return ans;
  }

  int search(vector<int>& nums, int target) {
    int leftIdx = binarySearch(nums, target, true);
    int rightIdx = binarySearch(nums, target, false) - 1;
    if (leftIdx <= rightIdx && rightIdx < nums.size() &&
        nums[leftIdx] == target && nums[rightIdx] == target) {
      return rightIdx - leftIdx + 1;
    }
    return 0;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
