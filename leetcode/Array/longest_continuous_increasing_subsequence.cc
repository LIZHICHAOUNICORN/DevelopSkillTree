#include <random>
#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

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
  int data[] = {1, 3, 5, 4, 7};
  vector<int> input(data, data + sizeof(data) / sizeof(int));
  Solution solu;
  int ret = solu.findLengthOfLCIS(input);
  return 0;
}
