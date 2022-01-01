#include <stack>
#include <cmath>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/number-of-digit-one/
// Solution:
// https://leetcode-cn.com/problems/number-of-digit-one/solution/zhao-ge-gui-lu-qing-song-de-chu-da-an-hu-p6l6/
// https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/mian-shi-ti-43-1n-zheng-shu-zhong-1-chu-xian-de-2/

class Solution {
 public:
  int countDigitOne(int n) {
    int e = 0;  //计数
    int r = 0;  //后面的数
    for (int i = 0; n != 0; i++) {
      int m = n / 10;  //有几个10
      if (m * 10 + 1 < n) {
        m++;  // 3421的情况
      } else if (m * 10 + 1 == n) {
        e += r + 1;  // 3413的情况
      }
      e += (m * pow(10, i));       //乘以位数
      r += (n % 10 * pow(10, i));  //更新后面的数
      n /= 10;                     //除以10，处理下一位
    }
    return e;
  }
};

class Solution1 {
 public:
  int countDigitOne(int n) {
    int digit = 1, res = 0;
    int high = n / 10, cur = n % 10, low = 0;
    while (high != 0 || cur != 0) {
      if (cur == 0)
        res += high * digit;
      else if (cur == 1)
        res += high * digit + low + 1;
      else
        res += (high + 1) * digit;
      low += cur * digit;
      cur = high % 10;
      high /= 10;
      digit *= 10;
    }
    return res;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.countDigitOne(2341);
  LOG(INFO) << ret;

  return 0;
}
