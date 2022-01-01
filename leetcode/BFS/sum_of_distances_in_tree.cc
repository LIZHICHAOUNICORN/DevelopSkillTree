#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/sum-of-distances-in-tree/
// Solution:
// https://leetcode-cn.com/problems/sum-of-distances-in-tree/solution/c-liang-ci-dfsde-dao-da-an-by-congwang357-2/

using namespace std;
class Solution {
 public:
  vector<int> ans;  //
  vector<int> cnt;
  vector<vector<int>>
      graph;  //存放边的关系，将与某个节点有边关系的所有节点都放到一个数组中
  int n = 0;  //存放节点数，放在全局是为了避免在DFS函数中传递

  //第一个DFS，通过累加得到根节点0到其他所有节点的距离和以及每个节点作为跟节点时其子树的节点数
  void dfs(int child, int parent) {
    for (int i = 0; i < graph[child].size(); i++) {
      if (graph[child][i] !=
          parent) {  //这里必须要判断，parent和child的子节点可能存在边关系，会造成重复计算，也会造成死循环
        dfs(graph[child][i], child);
        cnt[child] += cnt[graph[child][i]];
        ans[child] +=
            ans[graph[child][i]] +
            cnt[graph[child]
                     [i]];  //某个节点的距离和等于其各个字数的和+字数的大小
      }
    }
  }
  void dfs2(int child, int parent) {
    for (int i = 0; i < graph[child].size(); i++) {
      if (parent != graph[child][i]) {
        ans[graph[child][i]] =
            ans[child] - cnt[graph[child][i]] + n -
            cnt[graph
                    [child]
                    [i]];  //先计算出根节点的子节点，然后再递归去算子节点的子节点
        dfs2(graph[child][i], child);
      }
    }
  }
  vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
    if ((N == 0) || edges.empty()) {
      return {0};
    }

    n = N;
    graph.resize(N);
    ans.resize(N);
    cnt.resize(N);

    for (auto& c : cnt) {
      c = 1;
    }
    for (auto e : edges) {
      graph[e[0]].push_back(e[1]);
      graph[e[1]].push_back(e[0]);
    }

    dfs(0, -1);
    dfs2(0, -1);
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<int>> edges({{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}});

  Solution solu;
  auto ret = solu.sumOfDistancesInTree(6, edges);
  LOG(INFO) << ret.back();
  return 0;
}
