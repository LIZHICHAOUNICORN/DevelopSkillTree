#include <unordered_map>
#include <vector>

#include "leetcode/Tree/tree_node.h"
#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

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
 private:
  void in_order(TreeNode* node, int& sum, bool build) {
    if (node == nullptr) return;

    if (node->left) in_order(node->left, sum, build);
    if (build) {
      sum += node->val;
    } else {
      int node_val = node->val;
      node->val = sum;
      sum = sum - node_val;
    }
    if (node->right) in_order(node->right, sum, build);
  }

 public:
  TreeNode* convertBST(TreeNode* root) {
    if (root == nullptr) return root;

    int sum = 0;
    in_order(root, sum, true);
    in_order(root, sum, false);
    return root;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  TreeNode* node = solu.convertBST(nullptr);
  return 0;
}
