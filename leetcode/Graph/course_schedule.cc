#include <algorithm>
#include <queue>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/course-schedule/

// Topo sort
class Solution {
 private:
  // 存储有向图
  vector<vector<int>> edges;
  // 存储每个节点的入度
  vector<int> indeg;
  // 存储答案
  vector<int> result;

 public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    edges.resize(numCourses);
    indeg.resize(numCourses);
    for (const auto& info : prerequisites) {
      edges[info[1]].push_back(info[0]);
      ++indeg[info[0]];
    }

    queue<int> q;
    // 将所有入度为 0 的节点放入队列中
    for (int i = 0; i < numCourses; ++i) {
      if (indeg[i] == 0) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      // 从队首取出一个节点
      int u = q.front();
      q.pop();
      // 放入答案中
      result.push_back(u);
      for (int v : edges[u]) {
        --indeg[v];
        // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
        if (indeg[v] == 0) {
          q.push(v);
        }
      }
    }

    if (result.size() != numCourses) {
      return false;
    }
    return true;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  // Build test case.
  int numCourses = 2;
  vector<vector<int>> prerequisites({{1, 0}});

  Solution solu;
  bool ret = solu.canFinish(numCourses, prerequisites);
  LOG(INFO) << "ret: " << ret;

  return 0;
}
