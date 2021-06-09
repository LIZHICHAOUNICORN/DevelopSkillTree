// Author: Zhichao Li
// Time: 2021年06月09日
#include <map>
#include <iostream>
#include <algorithm>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using std::map;


// Time O(n)
// Space O(n)
class Solution {
public:
    int integerBreak(int n) {
       map<int, int> cache;
       cache[2] = 1;
       cache[3] = 2;
       cache[4] = 4;
       for (int i = 5; i <= n; ++i) {
           int end = i/2;
           int i_max = i;
           for (int j = i-2; j >= end; --j) {
               int a = std::max(cache[j], j);
               int b = std::max(cache[i-j], i-j);
               if (a*b > i_max) {
                   i_max = a*b;
               }
               cache[i] = i_max;
           }
       }
       return cache[n];
    }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.integerBreak(6);
  std::cout << "ret: " << ret << std::endl;
  // LOG(INFO) << ret;
  return 0;
}
