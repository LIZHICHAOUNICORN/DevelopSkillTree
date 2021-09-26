#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/

class KthLargest {
 public:
  priority_queue<int, vector<int>, greater<int>> q;
  int k;
  KthLargest(int k, vector<int>& nums) {
    this->k = k;
    for (auto& x : nums) {
      add(x);
    }
  }

  int add(int val) {
    q.push(val);
    if (q.size() > k) {
      q.pop();
    }
    return q.top();
  }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
