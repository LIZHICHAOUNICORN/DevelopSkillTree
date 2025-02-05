#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  string smallestGoodBase(string n) {
    long nVal = stol(n);
    int mMax = floor(log(nVal) / log(2));
    for (int m = mMax; m > 1; m--) {
      int k = pow(nVal, 1.0 / m);
      long mul = 1, sum = 1;
      for (int i = 0; i < m; i++) {
        mul *= k;
        sum += mul;
      }
      if (sum == nVal) {
        return to_string(k);
      }
    }
    return to_string(nVal - 1);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string ret = solu.smallestGoodBase("13");
  LOG(INFO) << ret;

  return 0;
}
