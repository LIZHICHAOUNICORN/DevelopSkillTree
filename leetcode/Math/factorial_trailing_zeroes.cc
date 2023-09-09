#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/factorial-trailing-zeroes/
// Solution:
// https://leetcode-cn.com/problems/factorial-trailing-zeroes/solution/c-shu-xue-xiang-xi-tui-dao-by-zeroac/

// 暴力解法
class Solution {
 public:
  int trailingZeroes(int n) {
    if (n == 0) return 0;
    int result = 1;
    for (int i = 2; i <= n; ++i) {
      result *= i;
    }

    string ret(std::to_string(result));

    int end = ret.size() - 1;
    if (ret[end] != 0) return 0;

    int nums = 1;
    for (int i = end - 1; i > 0; --i) {
      if (ret[i] != 0) break;
      nums += 1;
    }
    return nums;
  }
};

// math
class Solution {
 public:
  int trailingZeroes(int n) {
    int ans = 0;
    while (n != 0) {
      ans += n / 5;
      n /= 5;
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.trailingZeroes(5);
  LOG(INFO) << ret;

  return 0;
}
