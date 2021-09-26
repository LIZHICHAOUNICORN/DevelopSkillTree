#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::unordered_set;
using std::vector;
using std::pair;
using std::make_pair;
using std::max;

// 思路，按照题意判断方向然后行走，其中方向有{北，东，南，西}，初始化北方。
// -2：
// 向左90度对应的当前方向往左一个即(dir-1)%4，但是程序-1%4并不能得出3而是-1，所以正确的表示是(dir+3)%4。
// -1：
// 向右90度，对应的是方向转向下一个方向，即(dir+1)%4，通过取模来使得在四个方向来回循环转向。
// x：
// 正数为前进单位，最简单的方式可以一次一格前进，然后判断是否为障碍物，有则停止，没有则更新当前位置。

class Solution {
 public:
  struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
      auto h1 = std::hash<T1>{}(p.first);
      auto h2 = std::hash<T2>{}(p.second);
      return h1 ^ h2;
    }
  };

  int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    int dx[4] = {0, 1, 0, -1};  // 模拟前进时，对应方向的索引
    int dy[4] = {1, 0, -1, 0};  // 模拟前进时，对应方向的索引
    int x = 0, y = 0;           // 坐标
    int di = 0;                 // 方向

    unordered_set<pair<int, int>, pair_hash> obstacleSet;
    for (vector<int> obstacle : obstacles) {
      obstacleSet.insert(make_pair(obstacle[0], obstacle[1]));
    }

    int ans = 0;
    for (int cmd : commands) {
      if (cmd == -2)
        di = (di + 3) % 4;
      else if (cmd == -1)
        di = (di + 1) % 4;
      else {
        for (int k = 0; k < cmd; ++k) {
          int nx = x + dx[di];
          int ny = y + dy[di];
          if (obstacleSet.find(make_pair(nx, ny)) == obstacleSet.end()) {
            x = nx;
            y = ny;
            ans = max(ans, x * x + y * y);
          }
        }
      }
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> commands = {4, -1, 4, -2, 4};
  vector<vector<int>> obstacles = {{2, 4}};
  int ret = solu.robotSim(commands, obstacles);
  LOG(INFO) << ret;
  return 0;
}
