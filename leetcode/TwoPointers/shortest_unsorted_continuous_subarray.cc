#include <iostream>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::string;

// Problem:
// https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/

class Solution {
 public:
  int findUnsortedSubarray(vector<int>& nums) {
    if (is_sorted(nums.begin(), nums.end())) {
      return 0;
    }
    vector<int> numsSorted(nums);
    sort(numsSorted.begin(), numsSorted.end());
    int left = 0;
    while (nums[left] == numsSorted[left]) {
      left++;
    }
    int right = nums.size() - 1;
    while (nums[right] == numsSorted[right]) {
      right--;
    }
    return right - left + 1;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> nums({2, 6, 4, 8, 10, 9, 15});

  Solution solu;
  int ret = solu.findUnsortedSubarray(nums);
  LOG(INFO) << "ret " << ret;
  return 0;
}
