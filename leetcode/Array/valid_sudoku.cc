#include <set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 private:
  bool isValidCol(vector<vector<char>>& board) {
    set<int> table;
    for (int col = 0; col < board.size(); ++col) {
      table.clear();
      for (int i = 0; i < board[col].size(); ++i) {
        if (board[col][i] == '.') continue;
        if (table.count(board[col][i] - '0') != 0) {
          return false;
        }
        table.insert(board[col][i] - '0');
      }
    }
    return true;
  }
  bool isValidRow(vector<vector<char>>& board) {
    set<int> table;
    for (int row = 0; row < board.size(); ++row) {
      table.clear();
      for (int i = 0; i < board.size(); ++i) {
        if (board[i][row] == '.') continue;
        if (table.count(board[i][row] - '0') != 0) {
          return false;
        }
        table.insert(board[i][row] - '0');
      }
    }
    return true;
  }
  bool isValidSub(vector<vector<char>>& board, int pos, int row) {
    set<int> table;
    for (int i = pos; i < pos + 3; ++i) {
      for (int j = row; j < row + 3; ++j) {
        if (board[i][j] == '.') continue;
        if (table.count(board[i][j] - '0') != 0) {
          return false;
        }
        table.insert(board[i][j] - '0');
      }
    }
    return true;
  }

 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    bool col_ret = isValidCol(board);
    bool row_ret = isValidRow(board);
    if (!col_ret || !row_ret) return false;
    for (int i = 0; i < board.size(); i = i + 3) {
      for (int j = 0; j < board.back().size(); j = j + 3) {
        bool ret = isValidSub(board, i, j);
        if (!ret) return false;
      }
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  LOG(INFO) << "result";
  VLOG(1) << "vlog";
  return 0;
}
