#include <limits.h>
#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::max;

// recursive
// dp[n] = dp[n-1] + nums[n], nums[n])
class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    //类似寻找最大最小值的题目，初始值一定要定义成理论上的最小最大值
    int result = INT_MIN;
    int numsSize = int(nums.size());
    // dp[i]表示nums中以nums[i]结尾的最大子序和
    vector<int> dp(numsSize);
    dp[0] = nums[0];
    result = dp[0];
    for (int i = 1; i < numsSize; i++) {
      dp[i] = max(dp[i - 1] + nums[i], nums[i]);
      result = max(result, dp[i]);
    }
    return result;
  }
};

class Solution1 {
 public:
  int maxSubArray(vector<int>& nums) {
    int result = INT32_MIN;
    int count = 0;
    for (int i = 0; i < nums.size(); ++i) {
      count += nums[i];
      if (count > result) {
        result = count;
      }
      if (count < 0) count = 0;
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int ret = solu.maxSubArray(nums);
  LOG(INFO) << ret;
  return 0;
}
