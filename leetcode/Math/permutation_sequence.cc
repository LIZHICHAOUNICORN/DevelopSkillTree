#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <vector>
#include <numeric>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/permutation-sequence/

class Solution {
 public:
  string getPermutation(int n, int k) {
    vector<int> factorial(n);
    factorial[0] = 1;
    for (int i = 1; i < n; ++i) {
      factorial[i] = factorial[i - 1] * i;
    }

    --k;
    string ans;
    vector<int> valid(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
      int order = k / factorial[n - i] + 1;
      for (int j = 1; j <= n; ++j) {
        order -= valid[j];
        if (!order) {
          ans += (j + '0');
          valid[j] = 0;
          break;
        }
      }
      k %= factorial[n - i];
    }
    return ans;
  }
};

class Solution1 {
  static constexpr array<int,9> factorial{ {1, 1, 2, 6, 24, 120, 720, 5040, 40320} };

 public:
  string getPermutation(int n, int k) {
    vector<int> nums(n, 0);
    iota(begin(nums), end(nums), 1);
    string ret;
    --k;
    for (int i = n - 1; i != -1; --i) {
      auto it = begin(nums) + k / factorial[i];
      ret += ('0' + *it);
      nums.erase(it);
      k %= factorial[i];
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string ret = solu.getPermutation(9, 20);
  LOG(INFO) << ret;

  return 0;
}
