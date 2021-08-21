#include <iostream>
#include <vector>
#include <stack>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/next-permutation
// Solution: https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/

// TowPointer.
class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
      int i = nums.size() - 2;
      while (i >= 0 && nums[i] >= nums[i + 1]) {
          i--;
      }
      if (i >= 0) {
          int j = nums.size() - 1;
          while (j >= 0 && nums[i] >= nums[j]) {
              j--;
          }
          swap(nums[i], nums[j]);
      }
      reverse(nums.begin() + i + 1, nums.end());
  }
};


int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  
  return 0;
}
