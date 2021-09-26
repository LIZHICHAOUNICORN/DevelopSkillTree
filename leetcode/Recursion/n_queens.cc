// Author: zhichaoli
// Time: 2020年02月12日

#include <string>
#include <vector>

#include <gperftools/profiler.h>
#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::string;

// backtracking
class Solution {
 public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> answer;
    if (n == 0) {
      return answer;
    }

    // Initialize the board with all '.' chars.
    string row(n, '.');
    vector<string> board(n, row);

    // Initialize the cols and diagonals vectors
    // with 0's to indicate that they haven't been
    // used.
    vector<int> cols(n, 0);
    vector<int> up_diagonals(2 * n - 1, 0);
    vector<int> down_diagonals(2 * n - 1, 0);

    GenerateSolutions(answer, board, cols, up_diagonals, down_diagonals, 0, n);

    return answer;
  }

 private:
  void GenerateSolutions(vector<vector<string>>& answer, vector<string>& board,
                         vector<int>& cols, vector<int>& up_diagonals,
                         vector<int>& down_diagonals, int row_index, int n) {
    if (row_index == n) {
      // If we've surpassed the last row index, then that means
      // the final queen was successfully placed and the board
      // should be added to the answer. Stop recursing.
      answer.push_back(board);
      return;
    }

    std::string& row_string = board[row_index];

    for (int x = 0; x < n; x++) {
      // For each x index in the row, see if a queen can be
      // placed there. A queen can be placed only if the
      // column has not yet been used, and the two diagonals
      // have not yet been used (i.e. have 0's in their
      // lookups in the respective data structures).
      if (cols[x] == 0) {
        int up_diagonal_index = (x + row_index);
        int down_diagonal_index = (x - row_index + n - 1);
        if (up_diagonals[up_diagonal_index] == 0 &&
            down_diagonals[down_diagonal_index] == 0) {
          // Place the queen, update the data structures to
          // indicate that those rows and diagonals are no
          // longer available, and recurse by moving onto
          // the next row.
          row_string[x] = 'Q';
          cols[x] = 1;
          down_diagonals[down_diagonal_index] = 1;
          up_diagonals[up_diagonal_index] = 1;

          GenerateSolutions(answer, board, cols, up_diagonals, down_diagonals,
                            row_index + 1, n);

          // Now that the recursive call has finished, back-
          // track by resetting the state that was set, above,
          // so that the next x value in the row can be
          // independently tested.
          row_string[x] = '.';
          cols[x] = 0;
          down_diagonals[down_diagonal_index] = 0;
          up_diagonals[up_diagonal_index] = 0;
        }
      }
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  ProfilerStart("my.prof");
  vector<vector<string>> ret = solu.solveNQueens(10);
  sleep(10);
  ProfilerStop();
  for (auto vec : ret) {
    LOG(INFO) << "start again";
    for (auto it : vec) {
      LOG(INFO) << it;
    }
  }
  return 0;
}
