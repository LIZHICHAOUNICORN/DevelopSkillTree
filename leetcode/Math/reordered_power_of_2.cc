#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/reordered-power-of-2/
// Solution:
// https://leetcode-cn.com/problems/reordered-power-of-2/solution/zhong-xin-pai-xu-de-dao-2-de-mi-by-leetc-4fvs/

// 暴力解法

class Solution {
 private:
  bool is_exp(int num) {
    while (num > 1) {
      if (num % 2 == 1) return false;
      num = num / 2;
    }
    if (num == 1) return true;
    return false;
  }

 public:
  bool reorderedPowerOf2(int n) {
    if (n == 1) return true;

    string n_str = std::to_string(n);
    std::sort(n_str.begin(), n_str.end());
    do {
      if (n_str[0] == '0') continue;
      int num = stoi(n_str);
      if (is_exp(num)) return true;
    } while (next_permutation(n_str.begin(), n_str.end()));

    return false;
  }
};

class Solution1 {
 private:
  bool is_exp(int num) {
    while (num > 1) {
      if (num % 2 == 1) return false;
      num = num / 2;
    }
    if (num == 1) return true;
    return false;
  }

 public:
  bool reorderedPowerOf2(int n) {
    if (n == 1) return true;

    string n_str = std::to_string(n);
    std::sort(n_str.begin(), n_str.end());
    do {
      if (n_str[0] == '0') continue;
      int num = stoi(n_str);
      if (is_exp(num)) return true;
    } while (next_permutation(n_str.begin(), n_str.end()));

    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  bool ret = solu.reorderedPowerOf2(128);
  LOG(INFO) << ret;

  return 0;
}
