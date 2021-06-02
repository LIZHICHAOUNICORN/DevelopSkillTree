// Author: zhichaoli
// Time: 2020年05月16日

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  int hammingWeight(uint32_t n) {
    int count = 0;
    size_t total = 32;
    while(total-- > 0) {
      if (n & 1) ++count;
      n >>= 1;
    }
    return count;
  }
};
int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  uint32_t n = 00000000000000000000000000001011;
  Solution solu;
  int ret = solu.hammingWeight(n);
  LOG(INFO) << ret;
  return 0;
}
