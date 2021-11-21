// Author: Zhichao Li
// Time: 2021年06月09日
#include <algorithm>
#include <iostream>
#include <map>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/integer-break/

using std::map;

// Time O(n)
// Space O(n)

class Solution {
 public:
  int integerBreak(int n) {
    unordered_map<int, int> cache;
    cache[2] = 1;
    cache[3] = 2;
    cache[4] = 4;
    for (int i = 5; i <= n; ++i) {
      int max_factor = 0;
      for (int j = i - 1; j >= i / 2; j--) {
        int factor_a = j;
        int factor_b = i - j;
        if (cache.count(factor_a) >= 1)
          factor_a = max(cache[factor_a], factor_a);
        if (cache.count(factor_b) >= 1)
          factor_b = max(cache[factor_b], factor_b);
        max_factor = max(max_factor, factor_a * factor_b);
      }
      cache[i] = max_factor;
    }
    return cache[n];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.integerBreak(6);
  std::cout << "ret: " << ret << std::endl;
  LOG(INFO) << ret;
  return 0;
}
