#include <random>
#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(input_value, 10, "input data");

using namespace std;

class Solution {
 public:
  bool isPowerOfTwo(int n) {
    if (n < 1 || (n % 2 != 0 && n > 1)) return false;
    while (n > 1) {
      if (n % 2 != 0) return false;
      n = n >> 1;
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  bool ret = solu.isPowerOfTwo(FLAGS_input_value);
  LOG(INFO) << ret;
  return 0;
}
