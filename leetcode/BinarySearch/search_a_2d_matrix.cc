#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if ( !matrix.size()||!matrix[0].size() ) {
        return false;
    }
    int t = -1;
    for(int i = 0;i < matrix.size();i++)
    {
        if(target <= matrix[i][matrix[i].size() - 1])
        {
             t = i;
             break;
        }
    }
    if(t == -1) {
      return false;
    }
    else {
        int l = 0;
        int r = matrix[t].size() - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if(matrix[t][mid] >= target) r = mid;
            else l = mid + 1;
        }
        if(matrix[t][l] == target) {
          return true;
        }
        else {
          return false;
        }
    }
  }
};

// left = 0, right = m x n - 1
class Solution1 {
  public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if (m == 0) return false;
    int n = matrix[0].size();

    // 二分查找
    int left = 0, right = m * n - 1;
    int pivotIdx, pivotElement;
    while (left <= right) {
      pivotIdx = (left + right) / 2;
      pivotElement = matrix[pivotIdx / n][pivotIdx % n];
      if (target == pivotElement) return true;
      else {
        if (target < pivotElement) right = pivotIdx - 1;
        else left = pivotIdx + 1;
      }
    }
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution1 solu;
  vector<vector<int>> matrix = {{1,3,5,7}, {10,11,16,20}, {23,30,34,50}};
  int target = 3;
  bool ret = solu.searchMatrix(matrix, target);
  LOG(INFO) << ret;
  return 0;
}
