#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int cur_diff = 0;
        int pre_diff = 0;
        int result = 1;
        for (int i = 0; i < nums.size()-1; ++i) {
            cur_diff = nums[i+1] - nums[i];
            if ((cur_diff > 0 && pre_diff <= 0) || (pre_diff >= 0 && cur_diff < 0)) {
                result += 1;
                pre_diff = cur_diff;
            }
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
