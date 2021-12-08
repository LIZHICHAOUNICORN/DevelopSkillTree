#include <algorithm>
#include <climits>
#include <map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
// Solution:
// https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/solution/er-cha-shu-de-zui-da-shen-du-by-leetcode-solution/

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

// DFS
class Solution {
 public:
  int maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
  }
};

// BFS
class Solution1 {
 public:
  int maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    int ret = 0;
    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int sz = q.size();
      while (sz > 0) {
        TreeNode *node = q.front();
        q.pop();
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
        sz -= 1;
      }
      ret += 1;
    }
    return ret;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = solu.maxDepth(nullptr);
  return 0;
}
