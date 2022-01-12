#include <algorithm>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/escape-a-large-maze/
// Solution:
// https://leetcode-cn.com/problems/escape-a-large-maze/solution/gong-shui-san-xie-bfs-gei-ding-zhang-ai-8w63o/

using namespace std;

static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
 private:
  // 在包围圈中
  static constexpr int BLOCKED = -1;
  // 不在包围圈中
  static constexpr int VALID = 0;
  // 无论在不在包围圈中，但在 n(n-1)/2 步搜索的过程中经过了 target
  static constexpr int FOUND = 1;

  static constexpr int BOUNDARY = 1000000;

 public:
  bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source,
                        vector<int>& target) {
    // block 点小于两个是无法阻隔亮点联通的。
    if (blocked.size() < 2) {
      return true;
    }

    // 是对blocked的二维坐标编码成一维坐标的hash 函数。
    auto hash_fn = [fn = hash<long long>()](const pair<int, int>& o)->size_t {
      // auto & [ x, y ] = o;
      const int& x = o.first;
      const int& y = o.second;
      return fn((long long)x << 20 | y);
    };
    // 对编码后一维blocked坐标存储在hash_blocked
    unordered_set<pair<int, int>, decltype(hash_fn)> hash_blocked(0, hash_fn);
    for (const auto& pos : blocked) {
      hash_blocked.emplace(pos[0], pos[1]);
    }
    // bfs 访问函数, 由于参数众多，所以实现为lamda表达式
    // 1) 计算最大面积的点数countdown
    // 2) 进行bfs, 如果到达终点直接返回，如果访问够点数，返回, 否则返回false
    auto bfs = [&](vector<int>& start, vector<int>& finish) -> int {
      int sx = start[0], sy = start[1];
      int fx = finish[0], fy = finish[1];
      int countdown = blocked.size() * (blocked.size() - 1) / 2;
      queue<pair<int, int>> q;
      q.emplace(sx, sy);
      unordered_set<pair<int, int>, decltype(hash_fn)> visited(0, hash_fn);
      visited.emplace(sx, sy);
      while (!q.empty() && countdown > 0) {
        // auto[x, y] = q.front();
        const pair<int, int> front_value = q.front();
        const int& x = front_value.first;
        const int& y = front_value.second;
        q.pop();
        for (int d = 0; d < 4; ++d) {
          int nx = x + dirs[d][0], ny = y + dirs[d][1];
          if (nx >= 0 && nx < BOUNDARY && ny >= 0 && ny < BOUNDARY &&
              !hash_blocked.count({nx, ny}) && !visited.count({nx, ny})) {
            if (nx == fx && ny == fy) {
              return FOUND;
            }
            --countdown;
            q.emplace(nx, ny);
            visited.emplace(nx, ny);
          }
        }
      }
      if (countdown > 0) {
        return BLOCKED;
      }
      return VALID;
    };

    // 首先从src 遍历到 tgt
    int result = bfs(source, target);
    if (result == FOUND) {
      return true;
    } else if (result == BLOCKED) {
      return false;
    } else {
      // 然后从 tgt 遍历到 src
      result = bfs(target, source);
      if (result == BLOCKED) {
        return false;
      }
      return true;
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<int>> blocked({{0, 1}, {1, 0}});
  vector<int> source({0, 0});
  vector<int> target({0, 2});

  Solution solu;
  auto ret = solu.isEscapePossible(blocked, source, target);
  LOG(INFO) << ret;
  return 0;
}
