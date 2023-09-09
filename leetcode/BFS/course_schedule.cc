#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/course-schedule/
// Solution:
// https://leetcode-cn.com/problems/course-schedule/solution/ke-cheng-biao-by-leetcode-solution/

using std::vector;
using std::queue;

// BFS
class Solution {
 private:
  vector<vector<int>> edges;
  vector<int> indeg;

 public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    edges.resize(numCourses);
    indeg.resize(numCourses);
    for (const auto& info : prerequisites) {
      edges[info[1]].push_back(info[0]);
      ++indeg[info[0]];
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
      if (indeg[i] == 0) {
        q.push(i);
      }
    }

    int visited = 0;
    while (!q.empty()) {
      ++visited;
      int u = q.front();
      q.pop();
      for (int v : edges[u]) {
        --indeg[v];
        if (indeg[v] == 0) {
          q.push(v);
        }
      }
    }

    return visited == numCourses;
  }
};

// DFS
class Solution1 {
 private:
  vector<vector<int>> edges;
  vector<int> visited;
  bool valid = true;

 public:
  void dfs(int u) {
    visited[u] = 1;
    for (int v : edges[u]) {
      if (visited[v] == 0) {
        dfs(v);
        if (!valid) {
          return;
        }
      } else if (visited[v] == 1) {
        valid = false;
        return;
      }
    }
    visited[u] = 2;
  }

  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    edges.resize(numCourses);
    visited.resize(numCourses);
    for (const auto& info : prerequisites) {
      edges[info[1]].push_back(info[0]);
    }
    for (int i = 0; i < numCourses && valid; ++i) {
      if (!visited[i]) {
        dfs(i);
      }
    }
    return valid;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> pre1({1, 0});
  vector<int> pre2({0, 1});
  vector<vector<int>> pre;
  pre.push_back(pre1);
  pre.push_back(pre2);

  Solution solu;
  bool ret = solu.canFinish(2, pre);
  LOG(INFO) << ret;
  return 0;
}
