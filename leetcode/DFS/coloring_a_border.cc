#include <algorithm>
#include <climits>
#include <map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/coloring-a-border/

using namespace std;

typedef pair<int, int> pii;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pii> borders;
        int originalColor = grid[row][col];
        visited[row][col] = true;
        dfs(grid, row, col, visited, borders, originalColor);
        for (auto & item : borders) {
            int& x = item.first;
            int& y = item.second;
            grid[x][y] = color;
        }
        return grid;
    }

    void dfs(vector<vector<int>>& grid, int x, int y, vector<vector<bool>> & visited, vector<pii> & borders, int originalColor) {
        int m = grid.size(), n = grid[0].size();
        bool isBorder = false;
        int direc[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int nx = direc[i][0] + x, ny = direc[i][1] + y;
            if (!(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == originalColor)) {
                isBorder = true;
            } else if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                dfs(grid, nx, ny, visited, borders, originalColor);
            }                
        }
        if (isBorder) {
            borders.emplace_back(x, y);
        }
    }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> g({1,1});
  vector<int> g1({1,2});
  vector<vector<int>> grid;
  grid.emplace_back(g);
  grid.emplace_back(g1);

  int row = 0;
  int col = 0;
  int color = 3;
  auto ret = solu.colorBorder(grid, row, col, color);
  return 0;
}
