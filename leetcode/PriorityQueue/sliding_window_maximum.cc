#include <algorithm>
#include <queue>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/sliding-window-maximum/

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    priority_queue<pair<int, int>> q;
    for (int i = 0; i < k; ++i) {
      q.emplace(nums[i], i);
    }
    vector<int> ans = {q.top().first};
    for (int i = k; i < n; ++i) {
      q.emplace(nums[i], i);
      while (q.top().second <= i - k) {
        q.pop();
      }
      ans.push_back(q.top().first);
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums({1, 3, -1, -3, 5, 3, 6, 7});

  Solution solu;
  vector<int> ret = solu.maxSlidingWindow(nums, 3);
  for (auto& r : ret) {
    LOG(INFO) << r;
  }
  return 0;
}
