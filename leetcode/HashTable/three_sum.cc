#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    unordered_set<int> hash, vis;
    sort(nums.begin(), nums.end());

    for (int st = 0; st < nums.size(); st++) {
      while (st != 0 && nums[st] == nums[st - 1]) st++;
      hash.clear();
      vis.clear();
      for (int i = st + 1; i < nums.size(); i++) {
        auto got = hash.find(-nums[st] - nums[i]);
        if (got == hash.end()) {
          hash.insert(nums[i]);
        } else {
          res.push_back({nums[st], nums[i], -nums[st] - nums[i]});
          vis.insert(-nums[st] - nums[i]);
        }
        if (vis.find(-nums[st] - nums[i]) != vis.end()) {
          hash.erase(-nums[st] - nums[i]);
        }
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
