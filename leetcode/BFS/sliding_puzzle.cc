#include <algorithm>
#include <cassert>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::map;
using std::set;
using std::vector;
using std::queue;
using std::string;
using std::pair;
using std::unordered_set;
using std::find;
using std::swap;

// Problem: https://leetcode-cn.com/problems/sliding-puzzle/
// Solution:
// https://leetcode-cn.com/problems/sliding-puzzle/solution/bfskuang-jia-miao-sha-ge-chong-yi-zhi-you-xi-by-la/

// BFS
class Solution {
 private:
  vector<vector<int>> neighbors = {{1, 3}, {0, 2, 4}, {1, 5},
                                   {0, 4}, {1, 3, 5}, {2, 4}};

 public:
  int slidingPuzzle(vector<vector<int>>& board) {
    // 枚举 status 通过一次交换操作得到的状态
    auto get = [&](string& status) -> vector<string> {
      vector<string> ret;
      int x = status.find('0');
      for (int y : neighbors[x]) {
        swap(status[x], status[y]);
        ret.push_back(status);
        swap(status[x], status[y]);
      }
      return ret;
    };

    string initial;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 3; ++j) {
        initial += char(board[i][j] + '0');
      }
    }
    if (initial == "123450") {
      return 0;
    }

    queue<pair<string, int>> q;
    q.emplace(initial, 0);
    unordered_set<string> seen = {initial};

    while (!q.empty()) {
      auto[status, step] = q.front();
      q.pop();
      for (auto&& next_status : get(status)) {
        if (!seen.count(next_status)) {
          if (next_status == "123450") {
            return step + 1;
          }
          q.emplace(next_status, step + 1);
          seen.insert(move(next_status));
        }
      }
    }

    return -1;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> row1 = {4, 1, 2};
  vector<int> row2 = {0, 5, 3};
  vector<vector<int>> board;
  board.emplace_back(row1);
  board.emplace_back(row2);
  int ret = solu.slidingPuzzle(board);
  LOG(INFO) << ret;
  return 0;
}
