// Author: Zhichao Li
// Time: 2021年06月08日

#include "glog/logging.h"
#include "gflags/gflags.h"


// Time O(n)
// Space O(1)
class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;
        int cur = 1;
        int pre = 0;
        int result = 0;
        for (size_t i = 2; i <= n; ++i) {
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
	int fib(int n) {
	  if (n < 2) return n;
	  return fib(n - 1) + fib(n - 2);
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
