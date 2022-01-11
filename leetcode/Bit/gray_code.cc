#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/gray-code/
// Solution:
// https://leetcode-cn.com/problems/gray-code/solution/ge-lei-bian-ma-by-leetcode-solution-cqi7/

DEFINE_int32(n, 10, "");

using namespace std;

class Solution {
 public:
  vector<int> grayCode(int n) {
    vector<int> res;
    // res至少分配2^n个元素的存储空间
    res.reserve(n << 1);
    // 首先添加的肯定是元素0
    res.push_back(0);
    for (int i = 1; i <= n; ++i) {
      int m = res.size();
      // 倒序遍历G(n-1)，相等于将G(n-1)进行乐翻转，在G(n-1)的最前面添加1，就完成相邻位相差1的构造了
      for (int j = m - 1; j >= 0; j--) {
        // 1<<(i-1) = 2^(i-1) =
        // 10...0；1的后面有i-1个0，加上这个二进制相等于在前面添加1了
        res.push_back(res[j] | (1 << (i - 1)));
      }
    }
    return res;
  }
};

class Solution1 {
 public:
  vector<int> grayCode(int n) {
    vector<int> ret(1 << n);
    for (int i = 0; i < ret.size(); i++) {
      ret[i] = (i >> 1) ^ i;
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  auto ret = solu.grayCode(FLAGS_n);
  for (int i = 0; i < ret.size(); ++i) {
    LOG(INFO) << ret[i];
  }

  return 0;
}
