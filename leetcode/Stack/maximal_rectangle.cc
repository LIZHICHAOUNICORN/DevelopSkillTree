#include <climits>
#include <stack>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problems: https://leetcode-cn.com/problems/maximal-rectangle/
// Solutions:
// https://leetcode-cn.com/problems/maximal-rectangle/solution/zui-da-ju-xing-by-leetcode-solution-bjlu/

// 暴力解法，遍历每个点
class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if (m == 0) {
      return 0;
    }
    int n = matrix[0].size();
    vector<vector<int>> left(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == '1') {
          left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
        }
      }
    }

    int ret = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == '0') {
          continue;
        }
        int width = left[i][j];
        int area = width;
        for (int k = i - 1; k >= 0; k--) {
          width = min(width, left[k][j]);
          area = max(area, (i - k + 1) * width);
        }
        ret = max(ret, area);
      }
    }
    return ret;
  }
};

// 单调栈
class Solution1 {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if (m == 0) {
      return 0;
    }
    int n = matrix[0].size();
    vector<vector<int>> left(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == '1') {
          left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
        }
      }
    }

    int ret = 0;
    for (int j = 0; j < n; j++) {  // 对于每一列，使用基于柱状图的方法
      vector<int> up(m, 0), down(m, 0);

      stack<int> stk;
      for (int i = 0; i < m; i++) {
        while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
          stk.pop();
        }
        up[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
      }
      stk = stack<int>();
      for (int i = m - 1; i >= 0; i--) {
        while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
          stk.pop();
        }
        down[i] = stk.empty() ? m : stk.top();
        stk.push(i);
      }

      for (int i = 0; i < m; i++) {
        int height = down[i] - up[i] - 1;
        int area = height * left[i][j];
        ret = max(ret, area);
      }
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<char> row1({'1','0','1','0','0'});
  vector<char> row2({'1','0','1','1','1'});
  vector<char> row3({'1','1','1','1','1'});
  vector<char> row4({'1','0','0','1','0'});

  vector<vector<char>> matrix;
  matrix.emplace_back(row1);
  matrix.emplace_back(row2);
  matrix.emplace_back(row3);
  matrix.emplace_back(row4);

  Solution solu;
  int ret = solu.maximalRectangle(matrix);
  LOG(INFO) << ret;

  return 0;
}
