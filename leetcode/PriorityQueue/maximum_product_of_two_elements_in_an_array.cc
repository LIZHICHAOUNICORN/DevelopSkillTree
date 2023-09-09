#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/maximum-product-of-two-elements-in-an-array/

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    if (nums.size() == 2) return (nums[0] - 1) * (nums[1] - 1);
    int max1, max2;
    max1 = min(nums[0], nums[1]);
    max2 = max(nums[0], nums[1]);
    for (int i = 2; i < nums.size(); i++) {
      if (nums[i] > max1) {
        max1 = min(nums[i], max2);
        max2 = max(nums[i], max2);
      }
    }
    return (max1 - 1) * (max2 - 1);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  // vector<int> test_case({2,7,4,1,8,1});
  vector<int> test_case({3, 4, 5, 2});
  Solution solu;
  int ret = solu.maxProduct(test_case);
  LOG(INFO) << "ret " << ret;
  return 0;
}
