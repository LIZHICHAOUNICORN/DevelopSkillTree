#include <vector>
#include <iostream>

#include "glog/logging.h"
#include "gflags/gflags.h"

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
// Time O(m * n)
// Space O(m * n)
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid.front().size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (size_t i = 0; i < m && obstacleGrid[i][0] == 0; ++i) {
            dp[i][0] = 1;
        }
        for (size_t j = 0; j < n && obstacleGrid[0][j] == 0; ++j) {
            dp[0][j] = 1;
        }
        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j < n; ++j) {
                if(obstacleGrid[i][j] == 1) continue;
                dp[i][j] = dp[i - 1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<vector<int>> nums = {{0,0,0},{0,1,0},{0,0,0}};
  int ret = solu.uniquePathsWithObstacles(nums);
  LOG(INFO) << ret;
  return 0;
}
