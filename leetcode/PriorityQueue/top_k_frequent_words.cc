#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;
DEFINE_int32(n, 10, "test case value");

// Problem: https://leetcode-cn.com/problems/top-k-frequent-words/

class Solution {
 public:
  vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> cnt;
    for (auto& word : words) {
      cnt[word]++;
    }
    auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
      return a.second == b.second ? a.first < b.first : a.second > b.second;
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)>
        que(cmp);
    for (auto& it : cnt) {
      que.emplace(it);
      if (que.size() > k) {
        que.pop();
      }
    }
    vector<string> ret(k);
    for (int i = k - 1; i >= 0; i--) {
      ret[i] = que.top().first;
      que.pop();
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
