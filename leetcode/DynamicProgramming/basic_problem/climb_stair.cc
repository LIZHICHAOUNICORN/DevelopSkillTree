// Author: Zhichao Li
// Time: 2021年06月08日

#include "glog/logging.h"
#include "gflags/gflags.h"


// Time O(n)
// Space O(1)
class Solution {
public:
    int climb(int n) {
        if (n < 0) return 0;
        if (n <= 2) return n;
        int cur = 2;
        int pre = 1;
        int result = 0;
        for (size_t i = 3; i <= n; ++i) {
            result = cur + pre;
            pre = cur;
            cur = result;
        }
        return result;

    }
};

 
// Time O(2^n)
// Space O(n)
class Solution1 {
public:
	int climb(int n) {
      if (n < 0) return 0;
	  if (n < 2) return n;
	  return climb(n - 1) + climb(n - 2);
	} 
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.fib(2);
  LOG(INFO) << ret;
  return 0;
}
