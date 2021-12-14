#include <algorithm>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/trapping-rain-water/

class Solution {
 public:
  int trap(vector<int>& height) {
    int n = height.size();
    if (n == 0) {
      return 0;
    }
    vector<int> leftMax(n);
    leftMax[0] = height[0];
    for (int i = 1; i < n; ++i) {
      leftMax[i] = max(leftMax[i - 1], height[i]);
    }

    vector<int> rightMax(n);
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      rightMax[i] = max(rightMax[i + 1], height[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += min(leftMax[i], rightMax[i]) - height[i];
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> height({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});

  Solution solu;
  bool ret = solu.trap(height);
  LOG(INFO) << ret;

  return 0;
}
