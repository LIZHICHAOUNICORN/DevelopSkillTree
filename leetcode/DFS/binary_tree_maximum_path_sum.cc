#include <algorithm>
#include <climits>
#include <map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/
// Solution:
// https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/solution/er-cha-shu-zhong-de-zui-da-lu-jing-he-by-ikaruga/

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};


class Solution {
 public:
  int maxPathSum(TreeNode* root, int& val) {
    if (root == nullptr) return 0;
    int left = maxPathSum(root->left, val);
    int right = maxPathSum(root->right, val);
    int lmr = root->val + max(0, left) + max(0, right);
    int ret = root->val + max(0, max(left, right));
    val = max(val, max(lmr, ret));
    return ret;
  }

  int maxPathSum(TreeNode* root) {
    int val = INT_MIN;
    maxPathSum(root, val);
    return val;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  auto ret = solu.maxPathSum(nullptr);
  return 0;
}
