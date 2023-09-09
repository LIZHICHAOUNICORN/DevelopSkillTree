#include <algorithm>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/
// Solutions: https://www.bilibili.com/video/BV1q5411A7fU?p=1

using std::vector;
using std::min;

class Solution {
 public:
  typedef long long LL;
  int findKthNumber(int n, int k) {
    int prefix = 1;
    k--;  // k记录要找的数字在prefix后的第几个
    while (k > 0) {
      int cnt = getCnt(n, prefix);  // 当前prefix 下有多少个元素;包含prefix
      if (cnt <= k) {               // 向右
        k -= cnt;
        prefix++;
      } else {  // 向下
        k--;
        prefix *= 10;
      }
    }
    return prefix;
  }
  int getCnt(LL n, LL prefix) {
    LL cnt = 0;
    for (LL first = prefix, second = prefix + 1; first <= n;
         first *= 10, second *= 10) {
      cnt += min(n + 1, second) - first;
    }
    return cnt;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.findKthNumber(200, 35);

  LOG(INFO) << "ret: " << ret;

  return 0;
}
