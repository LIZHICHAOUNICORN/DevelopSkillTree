#include <climits>
#include <functional>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::stack;
using std::string;
using std::function;
using namespace std;

// Problem: https://leetcode-cn.com/problems/n-queens/
// Solutions:
// https://leetcode-cn.com/problems/n-queens/solution/nhuang-hou-by-leetcode-solution/

class Solution {
 public:
  vector<vector<string>> solveNQueens(int n) {
    auto solutions = vector<vector<string>>();
    auto queens = vector<int>(n, -1);
    auto columns = unordered_set<int>();
    auto diagonals1 = unordered_set<int>();
    auto diagonals2 = unordered_set<int>();
    backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);
    return solutions;
  }

  void backtrack(vector<vector<string>> &solutions, vector<int> &queens, int n,
                 int row, unordered_set<int> &columns,
                 unordered_set<int> &diagonals1,
                 unordered_set<int> &diagonals2) {
    if (row == n) {
      vector<string> board = generateBoard(queens, n);
      solutions.push_back(board);
    } else {
      for (int i = 0; i < n; i++) {
        if (columns.find(i) != columns.end()) {
          continue;
        }
        int diagonal1 = row - i;
        if (diagonals1.find(diagonal1) != diagonals1.end()) {
          continue;
        }
        int diagonal2 = row + i;
        if (diagonals2.find(diagonal2) != diagonals2.end()) {
          continue;
        }
        queens[row] = i;
        columns.insert(i);
        diagonals1.insert(diagonal1);
        diagonals2.insert(diagonal2);
        backtrack(solutions, queens, n, row + 1, columns, diagonals1,
                  diagonals2);
        queens[row] = -1;
        columns.erase(i);
        diagonals1.erase(diagonal1);
        diagonals2.erase(diagonal2);
      }
    }
  }

  vector<string> generateBoard(vector<int> &queens, int n) {
    auto board = vector<string>();
    for (int i = 0; i < n; i++) {
      string row = string(n, '.');
      row[queens[i]] = 'Q';
      board.push_back(row);
    }
    return board;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string board("WRRBBW");
  string hand("RB");

  Solution solu;
  auto ret = solu.solveNQueens(8);
  LOG(INFO) << ret.back().back();
  return 0;
}
