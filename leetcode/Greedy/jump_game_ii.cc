#include <limits.h>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;

// backtracking, timeout
//
class Solution {
 public:
  int jump(vector<int>& nums) {
    int ret = INT_MAX;
    int pos = 0;
    int sub_ret = 0;
    int size = nums.size() - 1;
    JumpHelper(nums, pos, sub_ret, size, &ret);
    return ret;
  }

 private:
  void JumpHelper(vector<int>& nums, int pos, int sub_ret, int size, int* ret) {
    if (pos >= size) {
      if (sub_ret < *ret) *ret = sub_ret;
      return;
    }

    int max_step = nums[pos];
    for (int i = 1; i <= max_step; ++i) {
      pos += i;
      JumpHelper(nums, pos, sub_ret + 1, size, ret);
      pos -= i;
    }
  }
};

class Solution1 {
 public:
  int jump(vector<int>& nums) {
    if (nums.size() <= 1) return 0;
    int curDistance = 0;
    int nextDistance = 0;
    int ans = 0;
    for (int i = 0; i < nums.size(); ++i) {
      nextDistance = max(nums[i] + i, nextDistance);
      if (i == curDistance) {
        if (curDistance != (nums.size() - 1)) {
          ++ans;
          curDistance = nextDistance;
          if (nextDistance >= nums.size() - 1) break;
        } else {
          break;
        }
      }
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> g = {5, 6, 4, 4, 6, 9, 4, 4, 7, 4, 4, 8, 2, 6, 8, 1, 5, 9, 6, 5,
                   2, 7, 9, 7, 9, 6, 9, 4, 1, 6, 8, 8, 4, 4, 2, 0, 3, 8, 5};
  int ret = solu.jump(g);
  LOG(INFO) << ret;
  return 0;
}
