#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// -231 <= x <= 231 - 1
class Solution {
 public:
  int reverse(int x) {
    bool add_sign = false;
    if (x < 0) {
      add_sign = true;
      if (x == INT_MIN) return 0;
      x = -x;
    }
    std::string x_str = std::to_string(x);
    std::reverse(x_str.begin(), x_str.end());
    int ret = std::atoi(x_str.c_str());
    if ((std::to_string(ret) != x_str) && (x % 10 != 0)) return 0;
    if (add_sign) {
      ret = -ret;
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.reverse(123);
  LOG(INFO) << ret;

  return 0;
}
