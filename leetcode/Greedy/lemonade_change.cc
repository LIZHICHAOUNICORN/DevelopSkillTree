#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::sort;

// hard code
class Solution {
 public:
  bool lemonadeChange(vector<int>& bills) {
    map<int, int> rest;
    rest[5] = 0;
    rest[10] = 0;
    rest[20] = 0;
    for (int i = 0; i < bills.size(); ++i) {
      if (bills[i] == 5) {
        rest[5] += 1;
        continue;
      }
      if (bills[i] == 10) {
        if (rest[5] > 0) {
          --rest[5];
          ++rest[10];
          continue;
        } else {
          return false;
        }
      }
      if (bills[i] == 20) {
        if (rest[5] > 0 and rest[10] > 0) {
          --rest[5];
          --rest[10];
          ++rest[20];
          continue;
        }
        if (rest[5] >= 3) {
          rest[5] -= 3;
          ++rest[20];
          continue;
        }
        return false;
      }
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
