#include <stack>
#include <vector>

#include "./tree_node.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

class Solution {
  int Iteration(TreeNode* node, int depth) {
    if (node == nullptr) return depth;

    int ret = max(Iteration(node->left, depth + 1),
                  Iteration(node->right, depth + 1));
    return ret;
  }

 public:
  int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    return max(Iteration(root->left, 1), Iteration(root->right, 1));
  }
};

class Solution1 {
 public:
  int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    queue<TreeNode*> Nodes;
    Nodes.push(root);
    int ret = 0;
    while (!Nodes.empty()) {
      int size = Nodes.size();
      for (int i = 0; i < size; ++i) {
        TreeNode* node = Nodes.front();
        Nodes.pop();
        if (node->left) Nodes.push(node->left);
        if (node->right) Nodes.push(node->right);
      }
      ret += 1;
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
