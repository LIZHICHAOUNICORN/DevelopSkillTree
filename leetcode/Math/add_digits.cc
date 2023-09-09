#include <stack>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  int addDigits(int num) {
    if (num < 10) return num;
    int sum(0);
    while (num) {
      sum += num % 10;
      num /= 10;
    }
    return addDigits(sum);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.addDigits(5);
  LOG(INFO) << ret;

  return 0;
}
