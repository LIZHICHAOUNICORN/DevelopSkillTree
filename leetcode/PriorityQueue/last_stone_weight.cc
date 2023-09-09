#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/last-stone-weight/

class Solution {
 public:
  typedef priority_queue<int, std::vector<int>, std::less<int>> Pri_Queue;
  int lastStoneWeight(vector<int>& stones) {
    if (stones.size() == 1) return stones.back();

    Pri_Queue sort_stones(stones.begin(), stones.end());
    while (sort_stones.size() > 1) {
      int x = sort_stones.top();
      sort_stones.pop();
      int y = sort_stones.top();
      VLOG(1) << "x " << x << ", y: " << y;
      sort_stones.pop();
      if (x > y) {
        swap(x, y);
      }
      if (x == y) {
        continue;
      } else {
        y = y - x;
        VLOG(1) << "x " << x << ", y: " << y;
        sort_stones.push(y);
        VLOG(1) << "top " << sort_stones.top()
                << ", size:" << sort_stones.size();
      }
    }
    VLOG(1) << "top " << sort_stones.top() << ", size:" << sort_stones.size()
            << ", empty: " << sort_stones.empty();

    int ret = 0;
    if (!sort_stones.empty()) {
      ret = sort_stones.top();
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  // vector<int> test_case({2,7,4,1,8,1});
  vector<int> test_case({2, 2});
  Solution solu;
  int ret = solu.lastStoneWeight(test_case);
  LOG(INFO) << "ret " << ret;
  return 0;
}
