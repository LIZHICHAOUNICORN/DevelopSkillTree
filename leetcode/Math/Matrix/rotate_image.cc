#include <vector>

#include <glog/logging.h>
#include <gflags/gflags.h>

using namespace std;
// Problem: https://leetcode-cn.com/problems/rotate-image/
// Solutions: https://leetcode-cn.com/problems/rotate-image/solution/xuan-zhuan-tu-xiang-by-leetcode-solution-vu3m/

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        auto matrix_new = matrix;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix_new[j][n - i - 1] = matrix[i][j];
            }
        }
        matrix = matrix_new;
    }
};

class Solution1 {
 public:
  void rotate(vector<vector<int>>& matrix) {
      int n = matrix.size();
      for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < (n + 1) / 2; ++j) {
          int temp = matrix[i][j];
          matrix[i][j] = matrix[n - j - 1][i];
          matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
          matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
          matrix[j][n - i - 1] = temp;
        }
      }
  }
};

class Solution2 {
 public:
  void rotate(vector<vector<int>>& matrix) {
      int n = matrix.size();
      // 水平翻转
      for (int i = 0; i < n / 2; ++i) {
          for (int j = 0; j < n; ++j) {
              swap(matrix[i][j], matrix[n - i - 1][j]);
          }
      }
      // 主对角线翻转
      for (int i = 0; i < n; ++i) {
          for (int j = 0; j < i; ++j) {
              swap(matrix[i][j], matrix[j][i]);
          }
      }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<vector<int>> input;
  vector<int> col1({1,2,3});
  vector<int> col2({4,5,6});
  vector<int> col3({7,8,9});
  input.push_back(col1);
  input.push_back(col2);
  input.push_back(col3);

  Solution solu;
  solu.rotate(input);
  return 0;
}
