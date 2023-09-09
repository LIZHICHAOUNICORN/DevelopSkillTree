#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::vector;

// base version: 3D DP;
class Solution {
 public:
  vector<int> getZerosOnes(std::string& str) {
    vector<int> zerosOnes(2);
    int length = str.length();
    for (int i = 0; i < length; i++) {
      zerosOnes[str[i] - '0']++;
    }
    return zerosOnes;
  }

  int findMaxForm(vector<std::string>& strs, int m, int n) {
    int length = strs.size();
    vector<vector<vector<int>>> dp(
        length + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
    for (int i = 1; i <= length; i++) {
      vector<int>&& zerosOnes = getZerosOnes(strs[i - 1]);
      int zeros = zerosOnes[0], ones = zerosOnes[1];
      for (int j = 0; j <= m; j++) {
        for (int k = 0; k <= n; k++) {
          dp[i][j][k] = dp[i - 1][j][k];
          if (j >= zeros && k >= ones) {
            dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][j - zeros][k - ones] + 1);
          }
        }
      }
    }
    return dp[length][m][n];
  }
};

// version 2, 2D DP
class Solution1 {
 public:
  vector<int> getZerosOnes(std::string& str) {
    vector<int> zerosOnes(2);
    int length = str.length();
    for (int i = 0; i < length; i++) {
      zerosOnes[str[i] - '0']++;
    }
    return zerosOnes;
  }

  int findMaxForm(vector<std::string>& strs, int m, int n) {
    int length = strs.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i < length; i++) {
      vector<int>&& zerosOnes = getZerosOnes(strs[i]);
      int zeros = zerosOnes[0], ones = zerosOnes[1];
      for (int j = m; j >= zeros; j--) {
        for (int k = n; k >= ones; k--) {
          dp[j][k] = std::max(dp[j][k], dp[j - zeros][k - ones] + 1);
        }
      }
    }
    return dp[m][n];
  }
};

int main(int argc, char* argv[]) {
  Solution solu;
  return 0;
}
