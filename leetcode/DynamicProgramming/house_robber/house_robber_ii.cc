#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// 由于成环，考虑max([1, n-1], [2, n])
class Solution {
 public:
  int robRange(vector<int>& nums, int start, int end) {
    int first = nums[start], second = max(nums[start], nums[start + 1]);
    for (int i = start + 2; i <= end; i++) {
      int temp = second;
      second = max(first + nums[i], second);
      first = temp;
    }
    return second;
  }

  int rob(vector<int>& nums) {
    int length = nums.size();
    if (length == 1) {
      return nums[0];
    } else if (length == 2) {
      return max(nums[0], nums[1]);
    }
    return max(robRange(nums, 0, length - 2), robRange(nums, 1, length - 1));
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> nums = {2, 3, 2};
  Solution solu;
  int ret = solu.rob(nums);
  LOG(INFO) << ret;
  return 0;
}
