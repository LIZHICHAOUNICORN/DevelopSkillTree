// Author: zhichaoli
// Time: 2020年05月16日

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/
// Solutions:
// https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/solution/leetcode-ac-dong-tai-gui-hua-jie-fa-han-eqceq/
// 			  https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/solution/shu-wei-dpmo-ban-ji-jie-fa-by-initness-let3/
//            https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/solution/suan-fa-xiao-ai-wo-lai-gei-ni-jie-shi-qi-4nh4/

class Solution {
 private:
  enum { N = 32 };
  int dp[N][2];

 public:
  int findIntegers(int n) {
    init();
    return dp_func(n);
  }

 private:
  void init() {
    dp[1][0] = 1, dp[1][1] = 1;  //只有1位时，最高位取0或1都是一个合法的数字
    for (int i = 2; i < N; ++i) {
      dp[i][0] = dp[i - 1][1] + dp[i - 1][0];  //最高位为0，低一位取0或1都可以
      dp[i][1] = dp[i - 1][0];  //最高位为1，低一位只能取0，来确保没有连续的一
    }
  }

  int dp_func(int n) {
    vector<int> nums;
    while (n) nums.push_back(n & 1), n >>= 1;  //将n转换为二进制并存在vector里面
    int last(0),
        res(0);                                 // res是当前已统计的合法数字数量，last是当前枚举的高一位的值
    for (int i = nums.size() - 1; i >= 0; --i)  //从最高位开始枚举
    {
      int x = nums[i];
      for (int j = 0; j < x; ++j)  //枚举从0到当前位减一
        res += dp
            [i + 1]
            [j];  //在当前位枚举到自己本身的值之前，它所包含的合法数字数量就对应了之前预处理出的dp值
      if (last == 1 && x == 1)
        break;   //当前位的值和高一位的值都是1时，说明数字已经不合法，直接break
      last = x;  // last记录为当前位
      if (!i)
        ++res;  //如果已经遍历到最低一位的本身的值，需要加上这个合法数字，对应的是图中右下方的方案
    }
    return res;  //返回结果
  }
};

class Solution1 {
 public:
  int findIntegers(int n) {
    // 预处理第 i 层满二叉树的路径数量
    vector<int> dp(31);
    dp[0] = dp[1] = 1;
    for (int i = 2; i < 31; ++i) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }

    // pre 记录上一层的根节点值，res 记录最终路径数
    int pre = 0, res = 0;
    for (int i = 29; i >= 0; --i) {
      int val = 1 << i;
      // if 语句判断 当前子树是否有右子树
      if ((n & val) != 0) {
        // 有右子树
        n -= val;
        res += dp[i + 1];  // 先将左子树（满二叉树）的路径加到结果中

        // 处理右子树
        if (pre == 1) {
          // 上一层为 1，之后要处理的右子树根节点肯定也为 1
          // 此时连续两个 1，不满足题意，直接退出
          break;
        }
        // 标记当前根节点为 1
        pre = 1;
      } else {
        // 无右子树，此时不能保证左子树是否为满二叉树，所以要在下一层再继续判断
        pre = 0;
      }

      if (i == 0) {
        ++res;
      }
    }

    return res;
  }
};

class Solution2 {
 public:
  int findIntegers(int n) {
    vector<int> f(32);
    f[0] = 1;
    f[1] = 2;
    for (int i = 2; i < 32; i++) f[i] = f[i - 1] + f[i - 2];
    string numStr = toBinary(n);
    int res = 0;
    for (int i = 0; i < numStr.size(); i++) {
      if (numStr[i] == '0') /* 选出numStr[i] = '1'的digit */
        continue;
      res += f[numStr.size() - i - 1];
      if (i != 0 && numStr[i - 1] == '1') return res;
    }
    return res + 1;
  }
  string toBinary(long n) /* 非负整数转二进制表示的字符串 */
  {
    string res = "";
    while (n > 0) {
      char r = n % 2 + '0';
      res.push_back(r); /* 记住: 放进去的结果会导致低位在前, 高位在后 */
      n /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  uint32_t n = 00000000000000000000000000001011;
  Solution solu;
  int ret = solu.hammingWeight(n);
  LOG(INFO) << ret;
  return 0;
}
