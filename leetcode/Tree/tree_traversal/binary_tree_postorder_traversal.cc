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
        Traversal(node->left, value);
        Traversal(node->right, value);
        value.push_back(node->val);
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (root == nullptr) return ret;
        Traversal(root, ret);
        return ret;

    }
};

class Solution1 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (root == nullptr) return ret;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()) {
            TreeNode* cur = st.top();
            st.pop();
            ret.push_back(cur->val);
            if (cur->left) st.push(cur->left);
            if (cur->right) st.push(cur->right);
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
