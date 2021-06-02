#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::sort;

class Solution {
 public:
  int findContentChildren(vector<int>& g, vector<int>& s) {
    if (s.empty()|| g.empty()) return 0;

    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int  max_value = 0;
    size_t s_start = 0;

    for (int kid : g) {
      while (s_start < s.size()) {
        if (s[s_start] >= kid) {
          ++max_value;
          ++s_start;
          break;
        };
        ++s_start;
      }
    }

    return max_value;
  }
};


class Solution1 {
 public:
  int findContentChildren(vector<int>& g, vector<int>& s) {
    if (s.empty()|| g.empty()) return 0;

    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int gi = 0, si = 0;
    int max_value = 0;
    while(gi < g.size() && si < s.size()){
      if(s[si] >= g[gi]){
        max_value ++;
        si ++;
        gi ++;
      }
      else {
        si ++;
      }
    }

    return max_value;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> g = {1, 2, 3}, s = {1, 1};
  int ret = solu.findContentChildren(g, s);
  LOG(INFO) << ret;
  return 0;
}
