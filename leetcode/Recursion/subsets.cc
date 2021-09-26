// Author: zhichaoli
// Time: 2020年02月12日

#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ret;
    if (nums.empty()) return ret;
    vector<int> empty;
    ret.push_back(empty);
    for (size_t i = 0; i < nums.size(); ++i) {
      int level_length = ret.size();
      for (size_t j = 0; j < level_length; ++j) {
        vector<int> level(ret[j]);
        level.push_back(nums[i]);
        ret.push_back(level);
      }
    }
    return ret;
  }
};

// Recursive (Backtracking)
class Solution1 {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> subs;
    vector<int> sub;
    SubsetsHelper(nums, 0, sub, subs);
    return subs;
  }

 private:
  void SubsetsHelper(const vector<int>& nums, int i, vector<int>& sub,
                     vector<vector<int>>& subs) {
    subs.push_back(sub);
    for (int j = i; j < nums.size(); j++) {
      sub.push_back(nums[j]);
      SubsetsHelper(nums, j + 1, sub, subs);
      sub.pop_back();
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums = {1, 2, 3};
  vector<vector<int>> ret = solu.subsets(nums);
  return 0;
}
