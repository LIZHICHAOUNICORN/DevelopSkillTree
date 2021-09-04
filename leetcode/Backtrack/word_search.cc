#include <vector>
#include <iostream>
#include <string>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using std::vector;
using std::string;

// Problem: https://leetcode-cn.com/problems/word-search/

class Solution {
 private:
    int col = 0;
    int row = 0;

     bool backtracking(int m, int n, string& word, string & ret,
                       vector<vector<char>>& board, vector<vector<bool>>& visited) {
        if (ret.size() == word.size()) return true;
        
        // Prune
        if (board[m][n] != word[ret.size()-1]) return false;

        // 遍历周围
        bool cur_ret = false;
        if (m+1 < col && !visited[m+1][n]) {
            ret.push_back(board[m+1][n]);
            visited[m+1][n] = true;
            cur_ret != backtracking(m+1, n, word, ret, board, visited);
            ret.pop_back();
            visited[m+1][n] = false;
            if (cur_ret) return true;
        }
        if (m-1 >= 0 && !visited[m-1][n]) {
            ret.push_back(board[m-1][n]);
            visited[m-1][n] = true;
            cur_ret != backtracking(m-1, n, word, ret, board, visited);
            ret.pop_back();
            visited[m-1][n] = false;
            if (cur_ret) return true;

        }
        if (n+1 < row && !visited[m][n+1]) {
            ret.push_back(board[m][n+1]);
            visited[m][n+1] = true;
            cur_ret != backtracking(m, n+1, word, ret, board, visited);
            ret.pop_back();
            visited[m][n+1] = false;
            if (cur_ret) return true;

        }
        if (n-1 >= 0 && !visited[m][n-1]) {
            ret.push_back(board[m][n-1]);
            visited[m][n-1] = true;
            cur_ret != backtracking(m, n-1, word, ret, board, visited);
            ret.pop_back();
            visited[m][n-1] = false;
            if (cur_ret) return true;
        }
        return cur_ret;
     }
 public:
    
    bool exist(vector<vector<char>>& board, string word) {
        col = board.size();
        row = board.front().size();
        vector<vector<bool>> visited(col, vector<bool>(row, false));
        string ret;
        bool result = false;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                visited[i][j] = true;
                ret.push_back(board[i][j]);
                result = backtracking(i, j, word, ret, board, visited);
                if (result) return true;
                ret.pop_back();
                visited[i][j] = false;
            }
        }
        return false;
    }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<char> nums1({'A','B'});
  vector<char> nums2({'S','F'});
  vector<vector<char>> board;
  board.push_back(nums1);
  board.push_back(nums2);
  bool ret = solu.exist(board, "AB");
  return 0;
}
