#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::max;


// memory overflow
class Solution {
 public:
  int rob(vector<int>& nums) {
    size_t nums_size = nums.size();
    if (nums_size == 1) return nums[0];
    vector<int> cache_start(nums_size, -1);
    vector<int> cache_end(nums_size, -1);
           // 因为nums[0]和nums[nums_size-1]不能同时选择，
           // 那么就可以选择三种情况：
           // 1) 索引1到nums_size-2 区间的最大值
           // 2) 索引0到nums_size-2 区间的最大值
           // 3) 索引1到nums_size-1 区间的最大值
           // 比较三者最大值，即可，但是因为情况2和情况3都包含1，
           // 所以可以直接选择比较2，和3
    return max(helper(nums, nums_size-1, 0, cache_start),
               helper(nums, nums_size, 1, cache_end));
  }

  int helper(vector<int>&nums, int end, int i, vector<int> cache) {
      if (i >= end) return 0;

      if (cache[i] != -1) return cache[i];
      int ret =  max(helper(nums, end, i+1, cache),
                     helper(nums, end, i+2, cache) + nums[i]);
      cache[i] = ret;
      return ret;
  }
};

// pass , loop
class Solution1 {
 public:
	int rob(vector<int>& nums) {
	  if (nums.size() == 0) return 0;
	  if (nums.size() == 1) return nums[0];
	  return max(myRob(vector<int>(nums.begin(), nums.end() - 1)),
                 myRob(vector<int>(nums.begin() + 1, nums.end())));
	}
 private:
	int myRob(vector<int> nums) {
	  int pre = 0, cur = 0, tmp;
	  for (auto num : nums) {
	    tmp = cur;
	    cur = max(pre + num, cur);
	    pre = tmp;
	  }
	  return cur;
	}
};




int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> nums = {2,3,2};
  Solution solu;
  int ret = solu.rob(nums);
  LOG(INFO) << ret;
  return 0;
}
