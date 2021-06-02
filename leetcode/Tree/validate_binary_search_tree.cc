#include <vector>
#include <stack>

#include <limits.h>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    return inorderTraversal(root);
  }
 private:
  bool inorderTraversal(TreeNode* root) {
    if (root == nullptr) return true;
    stack<TreeNode*> reverse;
    TreeNode *cur = root;
    int last_value = INT_MIN;
    bool last_value_init = false;
    while (cur != nullptr || !reverse.empty()){
      while (cur != nullptr) {
        reverse.push(cur);
        cur = cur->left;
      }
      cur = reverse.top();
      reverse.pop();
      if (cur->val <= last_value && last_value_init) return false;
      last_value = cur->val;
      if (!last_value_init) last_value_init = true;
      cur = cur->right;
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
