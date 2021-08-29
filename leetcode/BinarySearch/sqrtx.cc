#include <vector>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using std::vector;

class Solution {
 public:
    int mySqrt(int x) {
        if (x <= 1) return x;
        int l = 0;
        int r = x;
        long mid = 0;
        while (l < r) {
            mid = l + (r-l)/2;
            if (mid*mid == x) return mid;
            if (mid*mid > x) {
                r = mid - 1;
            } else if (mid*mid < x) {
                l = mid + 1;
            }
        }
        mid += 1;
        while (mid*mid > x) {
            mid -= 1;
        }
        return mid;

    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.mySqrt(10);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
