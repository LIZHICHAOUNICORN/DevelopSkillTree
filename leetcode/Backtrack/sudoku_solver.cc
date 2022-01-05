#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::stack;
using std::string;
using std::function;
using namespace std;

// Problem: https://leetcode-cn.com/problems/sudoku-solver/

class Solution {
 private:
  bool line[9][9];
  bool column[9][9];
  bool block[3][3][9];
  bool valid;
  vector<pair<int, int>> spaces;

 public:
  void dfs(vector<vector<char>>& board, int pos) {
    if (pos == spaces.size()) {
      valid = true;
      return;
    }

    pair<int, int>& space = spaces[pos];
    int i = space.first;
    int j = space.second;
    for (int digit = 0; digit < 9 && !valid; ++digit) {
      if (!line[i][digit] && !column[j][digit] && !block[i / 3][j / 3][digit]) {
        line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = true;
        board[i][j] = digit + '0' + 1;
        dfs(board, pos + 1);
        line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = false;
      }
    }
  }

  void solveSudoku(vector<vector<char>>& board) {
    memset(line, false, sizeof(line));
    memset(column, false, sizeof(column));
    memset(block, false, sizeof(block));
    valid = false;

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          spaces.emplace_back(i, j);
        } else {
          int digit = board[i][j] - '0' - 1;
          line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = true;
        }
      }
    }

    dfs(board, 0);
  }
};

// 使用位压缩
class Solution1 {
 private:
  int line[9];
  int column[9];
  int block[3][3];
  bool valid;
  vector<pair<int, int>> spaces;

 public:
  void flip(int i, int j, int digit) {
    line[i] ^= (1 << digit);
    column[j] ^= (1 << digit);
    block[i / 3][j / 3] ^= (1 << digit);
  }

  void dfs(vector<vector<char>>& board, int pos) {
    if (pos == spaces.size()) {
      valid = true;
      return;
    }

    const auto& it = spaces[pos];
    int i = it.first;
    int j = it.second;
    int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;
    for (; mask && !valid; mask &= (mask - 1)) {
      int digitMask = mask & (-mask);
      int digit = __builtin_ctz(digitMask);
      flip(i, j, digit);
      board[i][j] = digit + '0' + 1;
      dfs(board, pos + 1);
      flip(i, j, digit);
    }
  }

  void solveSudoku(vector<vector<char>>& board) {
    memset(line, 0, sizeof(line));
    memset(column, 0, sizeof(column));
    memset(block, 0, sizeof(block));
    valid = false;

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          spaces.emplace_back(i, j);
        } else {
          int digit = board[i][j] - '0' - 1;
          flip(i, j, digit);
        }
      }
    }

    dfs(board, 0);
  }
};

void PrintVector(const vector<char> cantainer) {
  for (const char& c : cantainer) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<char>> board({{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                              {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                              {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                              {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                              {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                              {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                              {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                              {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                              {'.', '.', '.', '.', '8', '.', '.', '7', '9'}});
  LOG(INFO) << "ori board:";
  for (int i = 0; i < board.size(); ++i) {
    PrintVector(board[i]);
  }

  Solution solu;
  solu.solveSudoku(board);
  LOG(INFO) << "decode: ";
  for (int i = 0; i < board.size(); ++i) {
    PrintVector(board[i]);
  }
  return 0;
}
