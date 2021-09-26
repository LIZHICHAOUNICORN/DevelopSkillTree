#include <climits>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;

class Solution {
 public:
  bool isPerfectSquare(int num) {
    if (num == INT_MAX) return false;
    int left = 1;
    int right = num;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int tmp = std::min(mid, INT_MAX / mid) * mid;
      if (tmp == num)
        return true;
      else if (tmp < num)
        left = mid + 1;
      else if (tmp > num)
        right = mid - 1;
    }
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  bool ret = solu.isPerfectSquare(10);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
