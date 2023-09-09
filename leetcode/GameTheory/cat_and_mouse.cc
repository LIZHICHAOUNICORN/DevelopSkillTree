#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/cat-and-mouse/
// Solution:
// https://leetcode-cn.com/problems/cat-and-mouse/solution/mao-he-lao-shu-by-leetcode-solution-444x/

class Solution {
 public:
  static const int MOUSE_WIN = 1;
  static const int CAT_WIN = 2;
  static const int DRAW = 0;
  static const int MAXN = 51;
  int n;
  int dp[MAXN][MAXN][MAXN * 2];
  vector<vector<int>> graph;

  int catMouseGame(vector<vector<int>>& graph) {
    this->n = graph.size();
    this->graph = graph;
    memset(dp, -1, sizeof(dp));
    return getResult(1, 2, 0);
  }

  int getResult(int mouse, int cat, int turns) {
    if (turns == n * 2) {
      return DRAW;
    }
    if (dp[mouse][cat][turns] < 0) {
      if (mouse == 0) {
        dp[mouse][cat][turns] = MOUSE_WIN;
      } else if (cat == mouse) {
        dp[mouse][cat][turns] = CAT_WIN;
      } else {
        getNextResult(mouse, cat, turns);
      }
    }
    return dp[mouse][cat][turns];
  }

  void getNextResult(int mouse, int cat, int turns) {
    int curMove = turns % 2 == 0 ? mouse : cat;
    int defaultResult = curMove == mouse ? CAT_WIN : MOUSE_WIN;
    int result = defaultResult;
    for (int next : graph[curMove]) {
      if (curMove == cat && next == 0) {
        continue;
      }
      int nextMouse = curMove == mouse ? next : mouse;
      int nextCat = curMove == cat ? next : cat;
      int nextResult = getResult(nextMouse, nextCat, turns + 1);
      if (nextResult != defaultResult) {
        result = nextResult;
        if (result != DRAW) {
          break;
        }
      }
    }
    dp[mouse][cat][turns] = result;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<int>> graph(
      {{2, 5}, {3}, {0, 4, 5}, {1, 4, 5}, {2, 3}, {0, 2, 3}});

  Solution solu;
  int ret = solu.catMouseGame(graph);
  LOG(INFO) << ret;
  return 0;
}
