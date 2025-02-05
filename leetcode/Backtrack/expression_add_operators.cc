#include <functional>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::string;
using std::function;

DEFINE_int32(target, 6, "target value");
DEFINE_string(nums, "123", "numbers");

// Problem: https://leetcode-cn.com/problems/expression-add-operators/

class Solution {
 public:
  vector<string> addOperators(string num, int target) {
    int n = num.length();
    vector<string> ans;

    function<void(string&, int, long, long)> backtrack = [&](
        string& expr, int i, long res, long mul) {
      if (i == n) {
        if (res == target) {
          ans.emplace_back(expr);
        }
        return;
      }
      int signIndex = expr.size();
      if (i > 0) {
        expr.push_back(0);  // 占位，下面填充符号
      }
      long val = 0;
      // 枚举截取的数字长度（取多少位），注意数字可以是单个 0 但不能有前导零
      for (int j = i; j < n && (j == i || num[i] != '0'); ++j) {
        val = val * 10 + num[j] - '0';
        expr.push_back(num[j]);
        if (i == 0) {  // 表达式开头不能添加符号
          backtrack(expr, j + 1, val, val);
        } else {  // 枚举符号
          expr[signIndex] = '+';
          backtrack(expr, j + 1, res + val, val);
          expr[signIndex] = '-';
          backtrack(expr, j + 1, res - val, -val);
          expr[signIndex] = '*';
          backtrack(expr, j + 1, res - mul + mul * val, mul * val);
        }
      }
      expr.resize(signIndex);
    };

    string expr;
    backtrack(expr, 0, 0, 0);
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  vector<string> ret = solu.addOperators(FLAGS_nums, FLAGS_target);
  for (auto& r : ret) {
    LOG(INFO) << r;
  }
  return 0;
}
