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
        if (node == nullptr) {
            return;
        }
        value.push_back(node->val);
        Traversal(node->left, value);
        Traversal(node->right, value);
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(root == nullptr) return ret;
        
        Traversal(root, ret);
        return ret;
    }
};

// stack
class Solution1 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> reverse;
        vector<int> ret;
        if (root == nullptr) return ret;
        reverse.push(root);
        while(!reverse.empty()) {
            TreeNode* node = reverse.top();
            reverse.pop();
            ret.push_back(node->val);
			// Note: first right, then left.
            // 为什么要先加入 右孩子，再加入左孩子呢? 
            // 因为这样出栈的时候才是中左右的顺序。
            if (node->right) reverse.push(node->right);
            if (node->left) reverse.push(node->left);
        }
        return ret;
    }
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
