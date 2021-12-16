#include <algorithm>
#include <queue>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/course-schedule-iii/
// Solution:
// https://leetcode-cn.com/problems/course-schedule-iii/solution/gong-shui-san-xie-jing-dian-tan-xin-yun-ghii2/

using namespace std;

class Solution {
 public:
  int scheduleCourse(vector<vector<int>>& courses) {
    sort(
        courses.begin(), courses.end(),
        [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });

    priority_queue<int> q;
    int day = 0;
    for (auto c : courses) {
      if (day + c[0] <= c[1]) {
        day += c[0];
        q.push(c[0]);
        continue;
      }
      if (!q.empty() && q.top() > c[0]) {
        day -= q.top();
        day += c[0];
        q.pop();
        q.push(c[0]);
      }
    }

    return q.size();
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> course1({100, 200});
  vector<int> course2({200, 1300});
  vector<int> course3({1000, 1250});
  vector<int> course4({2000, 3200});

  vector<vector<int>> courses;
  courses.emplace_back(course1);
  courses.emplace_back(course2);
  courses.emplace_back(course3);
  courses.emplace_back(course4);

  Solution solu;
  int ret = solu.scheduleCourse(courses);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
