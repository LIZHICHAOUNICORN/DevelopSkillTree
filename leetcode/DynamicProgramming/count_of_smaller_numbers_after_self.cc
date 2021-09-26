#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using std::vector;
using std::max;

class Solution {
 private:
  int FindFirstMinOffset(const vector<int>& nums, int offset, int target) {
    for (int j = offset + 1; j < nums.size(); ++j) {
      if (nums[j] < target) return j;
    }
    return nums.size() - 1;
  }

 public:
  vector<int> countSmaller(vector<int>& nums) {
    vector<int> counts(nums.size(), 0);
    int last_offset = nums.size() - 1;
    for (int j = nums.size() - 2; j >= 0; --j) {
      if (nums[j] > nums[j + 1]) {
        counts[j] = counts[j + 1] + 1;
        continue;
      }
      int min_offset = FindFirstMinOffset(nums, j + 1, nums[j]);
      std::cout << "min offset " << min_offset << std::endl;
      if (min_offset == last_offset && counts[j] == counts[min_offset]) {
        counts[j] = counts[min_offset];
        continue;
      }
      counts[j] = counts[min_offset] + 1;
    }
    return counts;
  }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {5, 2, 6, 1};
  solu.countSmaller(nums);
  return 0;
}
