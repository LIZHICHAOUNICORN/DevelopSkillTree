// Author: zhichaoli
// Time: 2020年05月23日

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  int hammingWeight(uint32_t n) {
    int ret = 0;
    for (int i = 0; i < 32; ++i) {
      ret += (n >> i & 1);
    }
    return ret;
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
