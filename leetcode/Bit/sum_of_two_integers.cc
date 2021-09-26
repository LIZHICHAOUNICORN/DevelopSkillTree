#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  int getSum(int a, int b) {
    while (b != 0) {
      unsigned int carry = (unsigned int)(a & b) << 1;
      a = a ^ b;
      b = carry;
    }
    return a;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.getSum(1, 2);
  LOG(INFO) << ret;
  return 0;
}
