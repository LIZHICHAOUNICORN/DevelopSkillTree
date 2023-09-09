#include <functional>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <climits>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::stack;
using std::string;
using std::function;
using namespace std;

// Problem: https://leetcode-cn.com/problems/zuma-game/

class Solution {
 public:
  int findMinStep(string board, string hand) {
    unordered_map<char, int> cnt;  // 用 cnt 作为遍历空间；避免取重复的球
    for (char b : hand) cnt[b]++;
    int ans = INT_MAX;
    dfs(board, cnt, 0, ans);
    return ans == INT_MAX ? -1 : ans;
  }

  void eliminate(string& board) {
    int l = 0;  // 连排的左边界
    int r = 0;  // 连排的右边界
    bool flag = false;
    for (; r <= board.size(); r++) {
      if (flag) {
        LOG(INFO) << board;
      }
      if (r < board.size() && board[r] == board[l]) continue;
      if (r - l >= 3) {  // 连排长度超过3 可以消除
        board.erase(l, r - l);
        // 消除后需要从头重新检查
        l = 0;
        r = 0;
      } else {
        // 左指针 指向 右指针
        l = r;
      }
    }
  }

  unordered_map<string, unordered_map<string, bool>>
      vis;  // 记录是不是已经搜索过当前状态
  // 发现 unordered_map 好像不能用 unordered_map 为 key
  // 手写了 hash 方法；用于判断当前状态是否已经搜索过
  string hash(unordered_map<char, int>& cnt) {
    string ans = "";
    for (auto p : cnt) {
      ans += p.first + to_string(p.second);
    }
    return ans;
  }

  void dfs(string& board, unordered_map<char, int>& cnt, int cur, int& ans) {
    if (board.empty()) {
      ans = min(ans, cur);
      return;
    }
    if (cnt.empty()) return;
    if (cur >= ans) return;

    if (!vis[board][hash(cnt)])
      vis[board][hash(cnt)] = true;
    else
      return;

    for (auto p : cnt) {  // 遍历所有球
      if (p.second == 0) continue;
      cnt[p.first]--;

      for (int i = 0; i < board.size(); i++) {  // 遍历所有插入的位置
        string board_ = board;
        board_.insert(board_.begin() + i, p.first);
        eliminate(board_);
        dfs(board_, cnt, cur + 1, ans);
      }

      cnt[p.first]++;
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string board("WRRBBW");
  string hand("RB");

  Solution solu;
  int ret = solu.findMinStep(board, hand);
  LOG(INFO) << ret;
  return 0;
}
