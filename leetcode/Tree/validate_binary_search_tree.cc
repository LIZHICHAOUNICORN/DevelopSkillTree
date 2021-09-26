#include <cstdlib>
#include <random>
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
  void inorder(TreeNode* node, vector<int>& value) {
    if (node == nullptr) return;
    inorder(node->left, value);
    value.push_back(node->val);
    inorder(node->right, value);
  }

 public:
  bool isValidBST(TreeNode* root) {
    if (root == nullptr) return false;
    vector<int> value;
    inorder(root, value);
    for (int i = 1; i < value.size(); ++i) {
      if (value[i] <= value[i - 1]) return false;
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  return 0;
}
