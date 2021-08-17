#include <iostream>
#include <vector>
#include <stack>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using namespace std;
// Warning: did't pass tests, bad case: [1,8,6,2,5]
class Solution {
 public:
  int maxArea(vector<int>& height) {
      vector<vector<int>> dp(height.size(), vector<int>(height.size(), 0));
      vector<int> min_value(height.size(), 0);
      min_value[0] = height[0];
      for (int i = 1; i < height.size(); ++i) {
        dp[i-1][i] = min(height[i], height[i-1]);
        min_value[i] = min(height[0], height[i]);
      }
      for (int j = 2; j < height.size(); ++j) {
          int value = min_value[j] * j;
          dp[0][j] = max(max(dp[0][j-1], dp[j-1][j]), value);
      }
      return dp[0][height.size()-1];
  }
};

class Solution {
 public:
  int maxArea(vector<int>& height) {
      int l = 0, r = height.size() - 1;
      int ans = 0;
      while (l < r) {
          int area = min(height[l], height[r]) * (r - l);
          ans = max(ans, area);
          if (height[l] <= height[r]) {
              ++l;
          }
          else {
              --r;
          }
      }
      return ans;
  }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> height({1,8,6,2,5});
  int ret = solu.maxArea(height);
  cout << ret << endl;
  
  return 0;
}
