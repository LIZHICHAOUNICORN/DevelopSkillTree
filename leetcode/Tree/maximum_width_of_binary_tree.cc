#include <queue>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/maximum-width-of-binary-tree/submissions/

// Definition for a binary tree node.
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
  int widthOfBinaryTree(TreeNode *root) {
    if (root == nullptr) return 0;
    queue<pair<TreeNode *, int>> q;  // pair的第二个位置记录当前是第几个节点
    q.push({root, 1});
    int width = 0;
    while (!q.empty()) {  // start是本层起点, index是本层当前遍历到的节点的索引
      int count = q.size();
      int start = q.front().second;
      int index = 0;
      while (count--) {
        TreeNode *tmp = q.front().first;
        index = q.front().second;
        q.pop();
        if (tmp->left)
          q.push({tmp->left, index * 2 - start * 2});  //防止索引位置太大溢出
        if (tmp->right) q.push({tmp->right, index * 2 + 1 - start * 2});
      }
      width = max(width, index - start + 1);
    }
    return width;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.widthOfBinaryTree(nullptr);
  LOG(INFO) << ret;
  return 0;
}
