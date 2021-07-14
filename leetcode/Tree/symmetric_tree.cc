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
    bool Symmetric(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right != nullptr) return false;
        if (left != nullptr && right == nullptr) return false;
        if (left == nullptr && right == nullptr) return true;
        if (left->val != right->val) return false;

        bool outside = Symmetric(left->left, right->right);
        bool inside = Symmetric(left->right, right->left);
        bool result = outside && inside;
        return result;
    }
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return Symmetric(root->left, root->right);
    }
};

class Solution1 {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        queue<TreeNode*> Nodes;
        Nodes.push(root->left);
        Nodes.push(root->right);
        while (!Nodes.empty()) {
            TreeNode* left = Nodes.front(); Nodes.pop();
            TreeNode* right = Nodes.front(); Nodes.pop();
            // 左右节点都为空
            if (!left && !right) {
                continue;
            }

            // 不对称情况
            if (!left || !right || (left->val != right->val)) {
                return false;
            }

            Nodes.push(left->left);
            Nodes.push(right->right);
            Nodes.push(left->right);
            Nodes.push(right->left);
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
