#include <vector>
#include <stack>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    if (root == nullptr) return ret;
    helper(root, ret);
    return ret;
  }
 private:
  void helper(TreeNode* root, vector<int>& node_value) {
    // 终止条件
    if (root == nullptr) return;
    // 处理当前层逻辑
    node_value.push_back(root->val);
    // 进入下层
    if (root->left != nullptr) {
        helper(root->left, node_value);
    }
    if (root->right != nullptr) {
        helper(root->right, node_value);
    }
    // 处理本层的资源
  }
};

// stack
class Solution2 {
 public:
  vector<int> preorderTraversal(TreeNode* root) {
  vector<int> ret;
  if (root == nullptr) return ret;
  stack<TreeNode*> reverse;
  TreeNode* cur = root;
  reverse.push(root);
  while (!reverse.empty()){
      cur = reverse.top();
      reverse.pop();
      ret.push_back(cur->val);
      if (cur->right != nullptr) {
          reverse.push(cur->right);
      }
      if (cur->left != nullptr) {
          reverse.push(cur->left);
      }
  }
  return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
