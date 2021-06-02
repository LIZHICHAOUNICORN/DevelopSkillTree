// Author: zhichaoli
// Time: 2020年02月12日

#include <vector>
#include <string>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"
#include <gperftools/profiler.h>

using std::vector;
using std::string;

class Solution {
 public:
  void recursion(vector<int> num, int i, int j, vector<vector<int> > &res) {
    if (i == j-1) {
      res.push_back(num);
      return;
    }
    for (int k = i; k < j; k++) {
      if (i != k && num[i] == num[k]) continue;
      std::swap(num[i], num[k]);
      recursion(num, i+1, j, res);
    }
  }
  vector<vector<int> > permuteUnique(vector<int> &num) {
    sort(num.begin(), num.end());
    vector<vector<int> >res;
    recursion(num, 0, num.size(), res);
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  ProfilerStart("my.prof");
  vector<int> num = {1, 2};
  vector<vector<int>> ret = solu.permuteUnique(num);
  ProfilerStop();
  for (auto vec : ret) {
    LOG(INFO) << "start again";
    for (auto it : vec) {
      LOG(INFO) << it;
    }
  }
  return 0;
}
