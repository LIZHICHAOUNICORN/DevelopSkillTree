// Author: zhichaoli
// Time: 2020年02月12日

#include <vector>
#include <unordered_map>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;
class Solution {
 public:
  double myPow(double x, int n) {
    long long N = n;
    double ret = 1.0;
    if (n == 0) return 1.0;
    bool neg = n < 0;
    if (neg) N = -N;
    ret = Pow(x, N);
    return neg ? 1/ret: ret;
  }
  // log(n)
  double Pow(double x, long long n) {
    if (n == 1) return x;
    double value = 1.0;
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = (n - 1)/2;
      value = x;
    }
    double half = Pow(x, n);
    return value * half * half;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  double ret = solu.myPow(2.0, 100);
  LOG(INFO) << "result: " << ret;
  return 0;
}
