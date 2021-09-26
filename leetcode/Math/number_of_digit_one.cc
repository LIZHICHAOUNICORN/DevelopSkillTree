#include <stack>
#include <vector>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using namespace std;

// 作者：ningfan
// 链接：https://leetcode-cn.com/problems/number-of-digit-one/solution/zhao-ge-gui-lu-qing-song-de-chu-da-an-hu-p6l6/

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

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;

  return 0;
}
