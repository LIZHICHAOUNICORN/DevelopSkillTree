#include <vector>
#include <cstdlib>
#include <random>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using namespace std;

class Solution {
 public:
  vector<int> runningSum(vector<int>& nums) {
      vector<int> ret(nums.size(), 0);
      ret[0] = nums[0];
      for (int i = 1; i < nums.size(); ++i) {
          ret[i] = ret[i-1] + nums[i];
      }
      return ret;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1,8,6,2,5,4,8,3,7};
  vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  Solution solu;
  vector<int> ret = solu.runningSum(input_value);
  for (int i = 0; i < ret.size(); ++i) {
    LOG(INFO) << "result: " << ret[i];
  }
  return 0;
}
