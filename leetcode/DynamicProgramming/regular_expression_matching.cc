#include <iostream>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

void Print2DVector(vector<vector<long>>& two_d_vector) {
  for (vector<long> vecs : two_d_vector) {
    for (long value : vecs) {
      cout << value << "\t";
    }
    cout << endl;
  }
}

class Solution {
 public:
  bool isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();

    auto matches = [&](int i, int j) {
      if (i == 0) {
        return false;
      }
      if (p[j - 1] == '.') {
        return true;
      }
      return s[i - 1] == p[j - 1];
    };

    vector<vector<int>> f(m + 1, vector<int>(n + 1));
    f[0][0] = true;
    for (int i = 0; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (p[j - 1] == '*') {
          f[i][j] |= f[i][j - 2];
          if (matches(i, j - 1)) {
            f[i][j] |= f[i - 1][j];
          }
        } else {
          if (matches(i, j)) {
            f[i][j] |= f[i - 1][j - 1];
          }
        }
      }
    }
    return f[m][n];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<vector<int>> nums = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  int ret = solu.uniquePathsWithObstacles(nums);
  LOG(INFO) << ret;
  return 0;
}
