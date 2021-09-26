#include <iostream>
#include <stack>
#include <vector>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/next-permutation
// Solution:
// https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/

class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    // 在尽可能靠右的低位进行交换，需要从后向前查找
    // 将一个 尽可能小的「大数」 与前面的「小数」交换
    // 将「大数」换到前面后，需要将「大数」后面的所有数重置为升序，升序排列就是最小的排列
    // 从最右边找较大值
    while (i >= 0 && nums[i] >= nums[i + 1]) {
      i--;
    }
    if (i >= 0) {
      int j = nums.size() - 1;
      // 从最右边找较小值
      while (j >= 0 && nums[i] >= nums[j]) {
        j--;
      }
      // 交换
      swap(nums[i], nums[j]);
    }
    //
    reverse(nums.begin() + i + 1, nums.end());
  }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;

  return 0;
}
