// Author: zhichaoli
// Time: 2020年02月13日

#include <vector>
#include <map>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::map;
using std::vector;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> statistics;
        size_t half = nums.size() / 2;
        if (nums.size() % 2 != 0) half += 1;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (statistics.find(nums[i]) == statistics.end()) {
                statistics[nums[i]] = 1;
            } else {
                ++statistics[nums[i]];
            }
            if (statistics[nums[i]] >= half) return nums[i];
        }
         return 0;
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {3, 2, 3};
  int ret = solu.majorityElement(nums);
  LOG(INFO) << "result: " << ret;
  return 0;
}
