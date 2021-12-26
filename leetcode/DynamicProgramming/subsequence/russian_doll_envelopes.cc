#include <algorithm>
#include <climits>
#include <functional>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::stack;
using std::string;
using std::function;
using namespace std;

// Problem: https://leetcode-cn.com/problems/russian-doll-envelopes/

// Timeout
class Solution {
 private:
  int check(const vector<int>& left, const vector<int>& right) {
    return (left.front() > right.front()) && (left.back() > right.back());
  }

  int backtrack(const vector<vector<int>>& envelopes, int index,
                vector<int>& used, int last) {
    if (index >= envelopes.size()) {
      return last;
    }
    int ret = last;

    for (int i = index; i < envelopes.size(); ++i) {
      vector<int> left({INT_MAX, INT_MAX});
      if (!used.empty()) {
        int left_index = used.back();
        left = envelopes[left_index];
      }
      if (check(left, envelopes[i])) {
        used.push_back(i);
        int value = last + 1;
        ret = max(ret, backtrack(envelopes, i + 1, used, value));
        used.pop_back();
      }
    }
    return ret;
  }

 public:
  int maxEnvelopes(vector<vector<int>>& envelopes) {
    int ret = 1;
    if (envelopes.size() == 1) return 1;

    // sort
    sort(envelopes.begin(), envelopes.end(),
         [](const vector<int>& left, const vector<int>& right) {
           if (left.front() == right.front()) {
             return left.back() > right.back();
           }
           return left.front() > right.front();
         });

    // backtrack
    vector<int> used;
    ret = backtrack(envelopes, 0, used, 0);

    return ret;
  }
};

// DP
class Solution1 {
 public:
  int maxEnvelopes(vector<vector<int>>& envelopes) {
    if (envelopes.empty()) {
      return 0;
    }

    int n = envelopes.size();
    sort(envelopes.begin(), envelopes.end(),
         [](const vector<int>& e1, const vector<int>& e2) {
           return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);
         });

    vector<int> f(n, 1);
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (envelopes[j][1] < envelopes[i][1]) {
          f[i] = max(f[i], f[j] + 1);
        }
      }
    }
    return *max_element(f.begin(), f.end());
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<int>> envelopes({{5, 4}, {6, 4}, {6, 7}, {2, 3}});

  Solution solu;
  auto ret = solu.maxEnvelopes(envelopes);
  LOG(INFO) << ret;
  return 0;
}
