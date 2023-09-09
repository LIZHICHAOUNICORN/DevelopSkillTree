#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/maximal-square/
// Solution:
// https://leetcode-cn.com/problems/maximal-square/solution/zui-da-zheng-fang-xing-by-leetcode-solution/

using std::vector;
using std::max;
using std::min;

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
      return 0;
    }
    int maxSide = 0;
    int rows = matrix.size(), columns = matrix[0].size();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (matrix[i][j] == '1') {
          // 遇到一个 1 作为正方形的左上角
          maxSide = max(maxSide, 1);
          // 计算可能的最大正方形边长
          int currentMaxSide = min(rows - i, columns - j);
          for (int k = 1; k < currentMaxSide; k++) {
            // 判断新增的一行一列是否均为 1
            bool flag = true;
            if (matrix[i + k][j + k] == '0') {
              break;
            }
            for (int m = 0; m < k; m++) {
              if (matrix[i + k][j + m] == '0' || matrix[i + m][j + k] == '0') {
                flag = false;
                break;
              }
            }
            if (flag) {
              maxSide = max(maxSide, k + 1);
            } else {
              break;
            }
          }
        }
      }
    }
    int maxSquare = maxSide * maxSide;
    return maxSquare;
  }
};

class Solution1 {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
      return 0;
    }
    int maxSide = 0;
    int rows = matrix.size(), columns = matrix[0].size();
    vector<vector<int>> dp(rows, vector<int>(columns));
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (matrix[i][j] == '1') {
          if (i == 0 || j == 0) {
            dp[i][j] = 1;
          } else {
            dp[i][j] =
                min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
          }
          maxSide = max(maxSide, dp[i][j]);
        }
      }
    }
    int maxSquare = maxSide * maxSide;
    return maxSquare;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<char> row1({'1', '0', '1', '0', '0'});
  vector<char> row2({'1', '0', '1', '1', '1'});
  vector<char> row3({'1', '1', '1', '1', '1'});
  vector<char> row4({'1', '0', '0', '1', '0'});
  vector<vector<char>> matrix;
  matrix.push_back(row1);
  matrix.push_back(row2);
  matrix.push_back(row3);
  matrix.push_back(row4);

  Solution solu;
  int ret = solu.maximalSquare(matrix);

  LOG(INFO) << ret;
  return 0;
}
