#include <vector>
#include <stack>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    void Traversal(TreeNode* node, vector<int>& value) {
        if (node == nullptr) return;

        Traversal(node->left, value);
        value.push_back(node->val);
        Traversal(node->right, value);
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (root == nullptr) return ret;
        Traversal(root, ret);
        return ret;
    }
};

// stack
class Solution2 {
 public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    if (root == nullptr) return ret;
    stack<TreeNode*> reverse;
    TreeNode *cur = root;
    while (cur != nullptr || !reverse.empty()){
      while (cur != nullptr) {
        reverse.push(cur);
        cur = cur->left;
      }
      cur = reverse.top();
      reverse.pop();
      ret.push_back(cur->val);
      cur = cur->right;
    }
    return ret;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
