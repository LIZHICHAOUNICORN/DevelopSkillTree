#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/the-k-weakest-rows-in-a-matrix/

class Solution {
 public:
  vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
    int m = mat.size(), n = mat[0].size();
    vector<pair<int, int>> power;
    for (int i = 0; i < m; ++i) {
      int l = 0, r = n - 1, pos = -1;
      while (l <= r) {
        int mid = (l + r) / 2;
        if (mat[i][mid] == 0) {
          r = mid - 1;
        } else {
          pos = mid;
          l = mid + 1;
        }
      }
      power.emplace_back(pos + 1, i);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q(power.begin(), power.end());
    vector<int> ans;
    for (int i = 0; i < k; ++i) {
      ans.push_back(q.top().second);
      q.pop();
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  return 0;
}
