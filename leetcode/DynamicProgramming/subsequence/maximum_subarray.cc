#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::max;


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int max_value = dp[0];
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = max(dp[i-1]+nums[i], nums[i]);
            if (dp[i] > max_value) max_value = dp[i];
        }
        return max_value;

    }
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
