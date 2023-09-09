#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::max;

class Solution {
 public:
  // nums: 数组
  // index: 当前选中的数组索引
  // last: 上次选择的值
  // len: 目前的子序列长度
  int helper(vector<int>& nums, int index, int last, int len) {
    if (index >= nums.size()) return len;

    int value = helper(nums, index + 1, last, len);
    if (last < nums[index]) {
      int this_value = helper(nums, index + 1, nums[index], len + 1);
      value = max(value, this_value);
    }
    return max(len, value);
  }
  int lengthOfLIS(vector<int>& nums) {
    int ret = max(helper(nums, 0, -10001, 0), helper(nums, 1, -10001, 0));
    return ret;
  }
};

class Solution1 {
 public:
  int lengthOfLIS(vector<int>& nums) {
    int len = nums.size();
    if (len <= 1) return len;
    vector<int> dp(len, 1);
    int result = 0;
    for (int i = 1; i < len; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
      }
      if (dp[i] > result) result = dp[i];
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int myints[] = {0, 1, 0, 3, 2, 3};
  vector<int> nums(myints, myints + sizeof(myints) / sizeof(int));
  int ret = solu.lengthOfLIS(nums);
  LOG(INFO) << ret;
  return 0;
}
