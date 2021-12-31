#include <algorithm>
#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/count-special-quadruplets/

using namespace std;

class Solution {
 public:
  int countQuadruplets(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    unordered_map<int, int> cnt;
    // c=n-2: 留出来d的值
    for (int c = n - 2; c >= 2; --c) {
      ++cnt[nums[c + 1]];
      // a 是最开始，但是要小于c的位置
      for (int a = 0; a < c; ++a) {
        //  b 是a的下一个位置开始
        for (int b = a + 1; b < c; ++b) {
          int sum = nums[a] + nums[b] + nums[c];
          if (cnt.count(sum)) {
            ans += cnt[sum];
          }
        }
      }
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> words({1, 1, 1, 3, 5});

  Solution solu;
  auto ret = solu.countQuadruplets(words);
  LOG(INFO) << ret;
  return 0;
}
