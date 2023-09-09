#include <set>
#include <vector>
#include <algorithm>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/meeting-rooms-ii/
// Solution:
// https://leetcode-cn.com/problems/meeting-rooms-ii/solution/tu-jie-zhuan-hua-wei-shang-xia-che-wen-t-uy2q/

using namespace std;

class Solution {
 public:
  int minMeetingRooms(vector<vector<int>>& intervals) {
    if (intervals.size() == 0) return 0;

    vector<pair<int, int>> meetings;
    for (const vector<int>& interval : intervals) {
      meetings.push_back({interval[0], 1});
      meetings.push_back({interval[1], -1});
    }
    sort(meetings.begin(), meetings.end());

    int cnt = 0, maxValue = 0;
    for (const pair<int, int>& meeting : meetings) {
      cnt += meeting.second;
      maxValue = max(maxValue, cnt);
    }
    return maxValue;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> interval1({0, 30});
  vector<int> interval2({0, 30});
  vector<int> interval3({0, 30});
  vector<vector<int>> intervals;
  intervals.emplace_back(interval1);
  intervals.emplace_back(interval2);
  intervals.emplace_back(interval3);

  Solution solu;
  int ret = solu.minMeetingRooms(intervals);
  LOG(INFO) << ret;
  return 0;
}
