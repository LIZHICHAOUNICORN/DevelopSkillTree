#include <limits.h>
#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::min;

// brute solute, timeout
class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.empty() || triangle.front().empty()) return 0;

    int min_value = INT_MAX;
    if (triangle.size() == 1) {
      for (int value : triangle.front()) {
        if (value < min_value) min_value = value;
      }
      return min_value;
    }

    int m = triangle.size();

    vector<int> dp(m + 1, INT_MAX);
    dp[0] = triangle[0][0];
    min_value =
        min(helper(triangle, dp, 1, 0), helper(triangle, dp, 1, 1)) + dp[0];
    return min_value;
  }

 private:
  int helper(const vector<vector<int>>& triangle, vector<int>& dp, int m,
             int n) {
    if (m == triangle.size() - 1) return triangle[m][n];

    int left = helper(triangle, dp, m + 1, n);
    int right = helper(triangle, dp, m + 1, n + 1);
    dp[m] = triangle[m][n] + min(left, right);
    return dp[m];
  }
};

class Solution1 {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    /* 自顶向下，考虑边界条件要特殊处理 , minPath[i][j] =
    Min()minPath[i-1][j-1], minPath[i-1][j]) + a[i][j],
    最左、右列要特殊处理
    最左： minPath[i][j] = minPath[i-1][j] + a[i][j]
    最右： minPath[i][j] = minPath[i-1][j-1] + a[i][j]
    */
    int rowSize = triangle.size();
    vector<vector<int>> minPath(triangle);
    if (triangle.size() == 1) {
      return triangle[0][0];
    }

    minPath[0][0] = triangle[0][0];
    minPath[1][0] = minPath[0][0] + triangle[1][0];
    minPath[1][1] = minPath[0][0] + triangle[1][1];

    for (int i = 2; i < triangle.size(); i++) {
      for (int j = 0; j < triangle[i].size(); j++) {
        // 最左侧
        if (j == 0) minPath[i][j] = minPath[i - 1][j] + triangle[i][j];
        // 最右侧
        else if (j == triangle[i].size() - 1)
          minPath[i][j] = minPath[i - 1][j - 1] + triangle[i][j];
        else
          minPath[i][j] =
              min(minPath[i - 1][j - 1], minPath[i - 1][j]) + triangle[i][j];
      }
    }
    // c++11新方法 max/ min_element 的使用请注意，不需要sort再打印了哦
    return *std::min_element(minPath[rowSize - 1].begin(),
                             minPath[rowSize - 1].end());
  }
};

class Solution2 {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    // 动态规划, 自底向上  递推式 dp[i][j] = min(dp[i+1][j], dp[i+1[j+1]) +
    // triangle[i][j];
    int rowSize = triangle.size();
    vector<vector<int>> dp(triangle);

    for (int i = rowSize - 2; i >= 0; i--) {
      for (int j = 0; j < triangle[i].size(); j++) {
        dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j];
      }
    }
    return dp[0][0];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
  int ret = solu.minimumTotal(triangle);
  LOG(INFO) << ret;

  vector<vector<int>> triangle1 = {{-1}, {-2, -3}};
  ret = solu.minimumTotal(triangle1);
  LOG(INFO) << ret;
  return 0;
}
