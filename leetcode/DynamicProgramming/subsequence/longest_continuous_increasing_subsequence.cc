#include <algorithm>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::string;
using std::max;

class Solution {
 public:
  int findLengthOfLCIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1);
    int max_value = 1;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] > nums[i - 1]) {
        dp[i] = dp[i - 1] + 1;
      }
      if (dp[i] > max_value) max_value = dp[i];
    }
    return max_value;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums({1, 3, 5, 4, 7});

  Solution solu;
  int ret = solu.findLengthOfLCIS(nums);
  LOG(INFO) << ret;
  return 0;
}
