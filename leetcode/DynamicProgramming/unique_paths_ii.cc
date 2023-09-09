#include <iostream>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

void Print2DVector(vector<vector<long>>& two_d_vector) {
  for (vector<long> vecs : two_d_vector) {
    for (long value : vecs) {
      cout << value << "\t";
    }
    cout << endl;
  }
}

// recursive
// dp[m][n] = dp[m-1][n] + dp[m][n-1]
// when m = 0 or n = 0; dp[m][n] =1
class Solution {
 public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid.front().size();
    if (m == 0 || n == 0) return 0;
    vector<vector<long>> cache(m, vector<long>(n, -1));
    if (obstacleGrid[0][0] == 1) {
      cache[0][0] = 0;
    } else {
      cache[0][0] = 1;
    }
    for (size_t i = 1; i < m; ++i) {
      if (obstacleGrid[i][0] == 1) {
        cache[i][0] = 0;
      } else {
        cache[i][0] = cache[i - 1][0];
      }
    }
    for (size_t i = 1; i < n; ++i) {
      if (obstacleGrid[0][i] == 1) {
        cache[0][i] = 0;
      } else {
        cache[0][i] = cache[0][i - 1];
      }
    }

    for (size_t j = 1; j < m; ++j) {
      for (size_t k = 1; k < n; ++k) {
        if (obstacleGrid[j][k] == 1) {
          cache[j][k] = 0;
        } else {
          cache[j][k] = cache[j - 1][k] + cache[j][k - 1];
        }
      }
    }
    Print2DVector(cache);
    return cache[m - 1][n - 1];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<vector<int>> nums = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  int ret = solu.uniquePathsWithObstacles(nums);
  LOG(INFO) << ret;
  return 0;
}
