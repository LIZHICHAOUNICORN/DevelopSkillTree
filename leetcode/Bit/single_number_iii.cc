#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  vector<int> singleNumber(vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int num : nums) {
      ++freq[num];
    }
    vector<int> ans;
    for (const auto & f : freq) {
      if (f.first == 1) {
        ans.push_back(f.second);
      }
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums({1, 2, 1, 3, 2, 5});

  Solution solu;
  auto ret = solu.singleNumber(nums);
  for (int i = 0; i < ret.size(); ++i) {
    LOG(INFO) << ret[i];
  }

  return 0;
}
