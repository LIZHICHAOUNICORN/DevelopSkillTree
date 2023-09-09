#include <vector>

#include <glog/logging.h>
#include <gflags/gflags.h>


using namespace std;
// Problem: https://leetcode-cn.com/problems/island-perimeter/

class Solution {
 public:
  vector<vector<int>> empty_perimeter;

  int area(vector<vector<int>>& grid, int i, int j) {
      // 如果是岛屿才计算，否则返回0
      // empty_perimeter 是单个变量也可。
      if (grid[i][j] == 1) {
          empty_perimeter[i][j] = 4;
      } else {
          return 0;
      }
      if (i-1 >= 0 && grid[i-1][j] == 1) {
          empty_perimeter[i][j] -= 1;
      }
      if (j-1 >= 0 && grid[i][j-1] == 1) {
          empty_perimeter[i][j] -= 1;
      }
      if (i+1 < grid.size() && grid[i+1][j] == 1) {
          empty_perimeter[i][j] -= 1;
      }
      if (j+1 < grid.front().size() && grid[i][j+1] == 1) {
          empty_perimeter[i][j] -= 1;
      }
      return empty_perimeter[i][j];

  }
  int islandPerimeter(vector<vector<int>>& grid) {
      int ret = 0;
      // init
      empty_perimeter = grid;
      for (int i = 0; i < grid.size(); ++i) {
          for (int j = 0; j < grid.front().size(); ++j) {
                  empty_perimeter[i][j] = 0;
          }
      }

      for (int i = 0; i < grid.size(); ++i) {
          for (int j = 0; j < grid.front().size(); ++j) {
              ret += area(grid, i, j);
          }
      }
      return ret;

  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<vector<int>> input;
  vector<int> col1({0,1,0,0});
  vector<int> col2({1,1,1,0});
  vector<int> col3({0,1,0,0});
  vector<int> col4({1,1,0,0});
  input.push_back(col1);
  input.push_back(col2);
  input.push_back(col3);
  input.push_back(col4);

  Solution solu;
  int ret = solu.islandPerimeter(input);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
