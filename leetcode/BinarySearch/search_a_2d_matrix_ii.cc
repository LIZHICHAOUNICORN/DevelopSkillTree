#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;

// Problem: https://leetcode-cn.com/problems/search-a-2d-matrix-ii/submissions/

// 暴力法
class Solution1 {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int min_val = matrix.front().front();
    int max_val = matrix.back().back();

    if (target < min_val || target > max_val) return false;

    for (int i = 0; i < matrix.size(); ++i) {
      if (matrix[i].back() < target) continue;
      for (int j = 0; j < matrix[0].size(); ++j) {
        if (matrix[i][j] == target) return true;
      }
    }
    return false;
  }
};

// 二分法
class Solution {
 private:
  bool BinarySearch(vector<vector<int>>& matrix, int target, int row) {
    int up = 0;
    int down = matrix[row].size() - 1;
    while (up <= down) {
      int mid = (up + down) / 2;
      if (matrix[row][mid] == target) return true;
      if (matrix[row][mid] > target) {
        down = mid - 1;
      } else {
        up = mid + 1;
      }
    }
    return false;
  }

 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int min_val = matrix.front().front();
    int max_val = matrix.back().back();

    if (target < min_val || target > max_val) return false;

    for (int i = 0; i < matrix.size(); ++i) {
      if (matrix[i].back() < target) continue;

      bool ret = BinarySearch(matrix, target, i);
      if (ret) return true;
      // for (int j = 0; j < matrix[0].size(); ++j) {
      //     if (matrix[i][j] == target) return true;
      // }
    }
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution1 solu;
  vector<vector<int>> matrix = {{1, 4, 7, 11, 15},
                                {2, 5, 8, 12, 19},
                                {3, 6, 9, 16, 22},
                                {10, 13, 14, 17, 24},
                                {18, 21, 23, 26, 30}};
  int target = 5;
  bool ret = solu.searchMatrix(matrix, target);
  LOG(INFO) << ret;
  return 0;
}
