#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::sort;

class Solution {
 private:
  static bool cmp(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
  }

 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() == 0) return 0;
    sort(intervals.begin(), intervals.end(), cmp);
    int count = 1;
    int end = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i) {
      if (end <= intervals[i][0]) {
        end = intervals[i][1];
        count++;
      }
    }
    return intervals.size() - count;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
