#include <stack>
#include <vector>

#include "./tree_node.h"

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];
  }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/majority-element/solution/duo-shu-yuan-su-by-leetcode-solution/
class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    int candidate = -1;
    int count = 0;
    for (int num : nums) {
      if (num == candidate)
        ++count;
      else if (--count < 0) {
        candidate = num;
        count = 1;
      }
    }
    return candidate;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
