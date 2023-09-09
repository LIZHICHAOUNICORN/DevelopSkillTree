#include <stack>
#include <vector>

#include "./tree_node.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) {
      return nullptr;
    }
    TreeNode* right = invertTree(root->right);
    TreeNode* left = invertTree(root->left);
    root->left = right;
    root->right = left;
    return root;
  }
};

class Solution1 {
 public:
  TreeNode* invertTree(TreeNode* root) {
    if (root) {
      invertTree(root->left);
      invertTree(root->right);
      std::swap(root->left, root->right);
    }
    return root;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  solu.invertTree(nullptr);
  return 0;
}
