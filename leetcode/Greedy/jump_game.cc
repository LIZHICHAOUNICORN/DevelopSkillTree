#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;

// Time Limit Exceeded
class Solution {
 public:
  bool canJump(vector<int>& nums) {
    vector<bool> index(nums.size(), false);
    index[0] = true;
    for (int i = 0; i < nums.size(); ++i) {
      // 设置 位置i+1后的
      for (int j = i + 1;
           (nums[i] > 0) && (j - i) <= nums[i] && j < nums.size(); ++j) {
        // bad case: [0,2,3]
        if (index[i]) index[j] = true;
      }
    }
    return index.back();
  }
};

// 自底向上的贪心算法
class Solution1 {
 public:
  bool canJump(vector<int>& nums) {
    if (nums.empty()) return true;
    if (nums.size() == 1 && nums[0] >= 1) return true;
    int pos = nums.size() - 1;
    for (int i = nums.size() - 2; i >= 0; --i) {
      if (pos - nums[i] <= i) pos = i;
    }
    return pos == 0;
  }
};

class Solution2 {
 public:
  bool canJump(vector<int>& nums) {
    int cover = 0;
    if (nums.size() == 1) return true;
    for (int i = 0; i <= cover; ++i) {
      cover = max(cover, nums[i] + i);
      if (cover >= nums.size() - 1) return true;
    }
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> g = {3, 2, 1, 0, 4};
  bool ret = solu.canJump(g);
  LOG(INFO) << ret;
  return 0;
}
