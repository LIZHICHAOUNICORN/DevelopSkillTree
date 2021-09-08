#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <utility>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/ipo/

class Solution {
 public:
  int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
      int ret = w;
      vector<bool> used(profits.size(), false);
      for (int i = 0; i < k; ++i) {
          int max_profits = 0;
          int use = -1;
          if (i == capital.size()) break;
          for (int j = 0; j < capital.size(); ++j) {
              if (capital[j] <= ret && profits[j] > max_profits && !used[j]) {
                  max_profits = profits[j];
                  use = j;
              }
          }
          if (use != -1) used[use] = true;
          ret += max_profits;
      }
      return ret;
  }
};


typedef pair<int,int> pii;

class Solution1 {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        int curr = 0;
        priority_queue<int, vector<int>, less<int>> pq;
        vector<pii> arr;

        for (int i = 0; i < n; ++i) {
            arr.push_back({capital[i], profits[i]});
        }
        sort(arr.begin(), arr.end());
        for (int i = 0; i < k; ++i) {
            while (curr < n && arr[curr].first <= w) {
                pq.push(arr[curr].second);
                curr++;
            }
            if (!pq.empty()) {
                w += pq.top();
                pq.pop();
            } else {
                break;
            }
        }

        return w;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
