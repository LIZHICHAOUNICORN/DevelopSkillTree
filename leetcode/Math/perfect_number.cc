#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/permutation-sequence/

class Solution {
 public:
  bool checkPerfectNumber(int num) {
    return num == 6 || num == 28 || num == 496 || num == 8128 ||
           num == 33550336;
  }
};

class Solution1 {
 public:
  bool checkPerfectNumber(int num) {
    int sum = 0;
    for (int i = 1; i <= num / 2; ++i) {
      if (num % i == 0) sum += i;
    }
    if (sum == num) return true;
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  bool ret = solu.checkPerfectNumber(28);
  LOG(INFO) << ret;

  return 0;
}
