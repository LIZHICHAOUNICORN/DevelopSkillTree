#include <algorithm>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::sort;

class Solution {
 private:
  static bool cmp(vector<int> a, vector<int> b) {
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] > b[0];
  }

 public:
  vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), cmp);
    vector<vector<int>> que;
    for (int i = 0; i < people.size(); ++i) {
      int position = people[i][1];
      que.insert(que.begin() + position, people[i]);
      // swap(people[i], people[people[i][1]]);
    }
    return que;
  }
};

class Solution1 {
 private:
  static bool cmp(vector<int> a, vector<int> b) {
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] > b[0];
  }

 public:
  vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), cmp);
    list<vector<int>> que;
    for (int i = 0; i < people.size(); ++i) {
      int position = people[i][1];
      std::list<vector<int>>::iterator it = que.begin();
      while (position--) {
        ++it;
      }
      que.insert(it, people[i]);
    }
    return vector<vector<int>>(que.begin(), que.end());
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
