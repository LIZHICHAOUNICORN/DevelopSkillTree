#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::max;

// timeout, recursive
class Solution {
 public:
  int rob(vector<int>& nums) {
      return helper(nums, 0);
  }
 private:
  // 返回 nums[start..] 能抢到的最大值
  int helper(vector<int>& nums, int i) {
    if (i >= nums.size()) return 0;
               // 抢，去下下家
    return max(nums[i] + helper(nums, i+2),
               // 不抢，去下家
               helper(nums, i+1));
  }
};

// pass, recursive
class Solution1 {
 public:
  int rob(vector<int>& nums) {
    vector<int> cache(nums.size(), -1);
    return helper(nums, 0, cache);
  }
 private:
  // 返回 nums[start..] 能抢到的最大值
  int helper(vector<int>& nums, int i, vector<int>& cache) {
    if (i >= nums.size()) return 0;

    if (cache[i] != -1) return cache[i];
                   // 抢，去下下家
    int ret =  max(nums[i] + helper(nums, i+2, cache),
                   // 不抢，去下家
                   helper(nums, i+1, cache));
    cache[i] = ret;
    return ret;
  }
};

// pass , loop
class Solution2 {
 public:
  int rob(vector<int>& nums) {
    int prev_max = 0;
    int curr_max = 0;
    for (int x : nums) {
      int temp = curr_max;
      curr_max = max(prev_max + x, curr_max);
      prev_max = temp;
    }
    return curr_max;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution1 solu;
  vector<int> nums = {1,2,3,1};
  int ret = solu.rob(nums);
  LOG(INFO) << ret;
  return 0;
}
