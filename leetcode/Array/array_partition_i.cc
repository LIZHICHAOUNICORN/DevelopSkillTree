#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/array-partition-i/

using namespace std;

class Solution {
 public:
  int arrayPairSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int ret = 0;
    for (int i = 0; i < nums.size(); i = i + 2) {
      ret += nums[i];
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> tasks({6, 2, 6, 5, 1, 2});

  Solution solu;
  int ret = solu.arrayPairSum(tasks);
  LOG(INFO) << ret;

  return 0;
}
