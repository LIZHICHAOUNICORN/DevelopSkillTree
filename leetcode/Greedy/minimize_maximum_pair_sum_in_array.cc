#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::sort;

class Solution {
public:
    int minPairSum(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n / 2; ++i) {
            res = max(res, nums[i] + nums[n - 1 - i]);
        }
        return res;
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> g = {1, 2, 3}, s = {1, 1};
  int ret = solu.findContentChildren(g, s);
  LOG(INFO) << ret;
  return 0;
}
