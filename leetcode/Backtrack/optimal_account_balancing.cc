#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/optimal-account-balancing/
// Solution:
// https://leetcode-cn.com/problems/optimal-account-balancing/solution/465-zui-you-zhang-dan-ping-heng-by-klb/

class Solution {
 public:
  int ans = INT_MAX;
  int minTransfers(vector<vector<int>>& transactions) {
    unordered_map<int, int> dict;
    vector<int> money;
    for (const auto& transaction : transactions) {
      dict[transaction[0]] -= transaction[2];
      dict[transaction[1]] += transaction[2];
    }
    for (const auto & it : dict) {
      int num = it.second;
      if (num != 0) {
        money.push_back(num);
      }
    }
    dfs(0, 0, money);
    return ans;
  }
  void dfs(int start, int count, vector<int>& money) {
    if (count > ans) return;
    while (start < money.size() && money[start] == 0) {
      ++start;
    }
    if (start == money.size()) {
      ans = min(ans, count);
      return;
    }
    for (int i = start + 1; i < money.size(); ++i) {
      if (money[i] * money[start] < 0) {
        money[i] += money[start];
        dfs(start + 1, count + 1, money);
        money[i] -= money[start];
      }
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<int>> transactions({{0, 1, 10}, {2, 0, 5}});

  Solution solu;
  int ret = solu.minTransfers(transactions);

  LOG(INFO) << ret;
  return 0;
}
