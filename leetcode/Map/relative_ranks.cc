#include <iostream>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::string;

// Problem: https://leetcode-cn.com/problems/relative-ranks/

class Solution {
 public:
  vector<string> findRelativeRanks(vector<int>& score) {
    int n = score.size();
    map<int, int, greater<int>> num2index;
    for (int i = 0; i < n; i++) {
      num2index[score[i]] = i;
    }
    vector<string> ans(n);
    int i = 0;
    for (auto mPair : num2index) {
      int index = mPair.second;
      if (i == 0) {
        ans[index] = "Gold Medal";
      } else if (i == 1) {
        ans[index] = "Silver Medal";
      } else if (i == 2) {
        ans[index] = "Bronze Medal";
      } else
        ans[index] += to_string(i + 1);
      i++;
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
