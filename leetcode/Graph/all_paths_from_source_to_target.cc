#include <algorithm>
#include <cstdlib>
#include <queue>
#include <random>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

// Problem: https://leetcode-cn.com/problems/all-paths-from-source-to-target
class Solution {
 public:
  vector<vector<int>> ans;
  vector<int> stk;

  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    stk.push_back(0);
    dfs(graph, 0, graph.size() - 1);
    return ans;
  }
  void dfs(vector<vector<int>>& graph, int src, int dst) {
    if (src == dst) {
      ans.push_back(stk);
    }

    for (int i = 0; i < graph[src].size(); ++i) {
      stk.push_back(graph[src][i]);
      dfs(graph, graph[src][i], dst);
      stk.pop_back();
    }
  }
};

class Solution1 {
 public:
  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    queue<vector<int>> que;
    que.push({0});

    while (!que.empty()) {
      auto path = que.front();
      que.pop();

      auto cur = path.back();
      for (auto& next : graph[cur]) {
        path.push_back(next);

        if (next == (int)graph.size() - 1) {
          ans.push_back(path);
        } else {
          que.push(path);
        }

        path.pop_back();
      }
    }

    return ans;
  }

 private:
  vector<vector<int>> ans;
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  // Build test case.
  vector<vector<int>> flights;
  vector<int> flight1({1, 2});
  vector<int> flight2({3});
  vector<int> flight3({3});
  vector<int> flight4({});
  flights.push_back(flight1);
  flights.push_back(flight2);
  flights.push_back(flight3);
  flights.push_back(flight4);

  Solution solu;
  auto paths = solu.allPathsSourceTarget(flights);
  return 0;
}
