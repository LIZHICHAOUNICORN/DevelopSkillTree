#include <cassert>
#include <vector>
#include <map>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::map;
using std::vector;

class Solution {
 public:
  bool lemonadeChange(vector<int>& bills) {
    if (bills.empty()) return true;
    map<int, int> saving;
    saving[5] = 0;
    saving[10] = 0;
    saving[20] = 0;
    for (int bill : bills) {
      if (bill == 5) {
        ++saving[5];
        continue;
      }
      if (bill == 10) {
        if (saving[5] == 0) return false;
        --saving[5];
        ++saving[10];
        continue;
      }
      if (bill == 20) {
        if (saving[5] == 0) return false;
        if (saving[10] > 0 && saving[5] > 0) {
          --saving[5];
          --saving[10];
          ++saving[20];
          continue;
        }
        if (saving[5] >= 3) {
          saving[5] -= 3;
          ++saving[20];
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
  vector<int> bills = {5,5,10,20,5,5,5,5,5,5,5,5,5,10,5,5,20,5,20,5};
  bool ret = solu.lemonadeChange(bills);
  LOG(INFO) << ret;
  return 0;
}
