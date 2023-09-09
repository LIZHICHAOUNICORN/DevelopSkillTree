#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    // 特判
    if (n == 0) {
      return res;
    }

    // 执行深度优先遍历，搜索可能的结果
    string cur_str;
    dfs(cur_str, n, n, res);
    return res;
  }

  /**
 * @param curStr 当前递归得到的结果
 * @param left   左括号还有几个可以使用
 * @param right  右括号还有几个可以使用
 * @param res    结果集
 */
  void dfs(string cur_str, int left, int right, vector<string>& res) {
    // 因为每一次尝试，都使用新的字符串变量，所以无需回溯
    // 在递归终止的时候，直接把它添加到结果集即可，注意与「力扣」第 46 题、第 39
    // 题区分
    if (left == 0 && right == 0) {
      LOG(INFO) << "cur_str: " << cur_str << ", left: " << left
                << ", right: " << right << ", push back";
      res.push_back(cur_str);
      return;
    }

    // 剪枝（如图，左括号可以使用的个数严格大于右括号可以使用的个数，才剪枝，注意这个细节）
    if (left > right) {
      LOG(INFO) << "cur_str: " << cur_str << ", left: " << left
                << ", right: " << right << ", return";
      return;
    }

    if (left > 0) {
      LOG(INFO) << "cur_str: " << cur_str << ", left: " << left
                << ", right: " << right << ", left > 0";
      dfs(cur_str + "(", left - 1, right, res);
    }

    if (right > 0) {
      LOG(INFO) << "cur_str: " << cur_str << ", left: " << left
                << ", right: " << right << ", right > 0";
      dfs(cur_str + ")", left, right - 1, res);
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<string> ret = solu.generateParenthesis(5);
  return 0;
}
