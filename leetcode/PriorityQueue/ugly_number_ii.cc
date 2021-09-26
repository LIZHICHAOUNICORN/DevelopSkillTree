#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;
DEFINE_int32(n, 10, "test case value");

// Problem: https://leetcode-cn.com/problems/ugly-number-ii/

class Solution {
 public:
  int nthUglyNumber(int n) {
    vector<int> factors({2, 3, 5});
    unordered_set<int> check;
    priority_queue<long, vector<long>, std::greater<long>> max_heap;
    check.insert(1L);
    max_heap.push(1L);

    int ret = 0;
    for (int i = 0; i < n; ++i) {
      long cur = max_heap.top();
      max_heap.pop();
      ret = cur;
      for (int factor : factors) {
        long next = factor * cur;
        if (!check.count(next)) {
          check.insert(next);
          max_heap.push(next);
        }
      }
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.nthUglyNumber(FLAGS_n);
  LOG(INFO) << "ret :" << ret;
  return 0;
}
