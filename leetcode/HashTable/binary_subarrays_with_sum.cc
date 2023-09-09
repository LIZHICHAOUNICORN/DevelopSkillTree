#include <string>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  int numSubarraysWithSum(vector<int>& nums, int goal) {
    int sum = 0;
    unordered_map<int, int> cnt;
    int ret = 0;
    for (auto& num : nums) {
      cnt[sum]++;
      sum += num;
      ret += cnt[sum - goal];
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> test_cast = {2, 7, 11, 15};
  Solution solu;
  vector<int> ret = solu.twoSum(test_cast, 9);
  return 0;
}
