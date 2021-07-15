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
    int getDepth(TreeNode* node) {
        if (node == nullptr) return 0;

        int depth = 0;
        int left_depth = getDepth(node->left);
        int right_depth = getDepth(node->right);
        // 右子树正常，左子树为空，非最低
        if (node->left == nullptr && node->right != nullptr) {
            return right_depth + 1;
        }
        // 左子树正常，右子树为空，非最低
        if (node->left != nullptr && node->right == nullptr) {
            return left_depth + 1;
        }

        return 1+min(left_depth, right_depth);

    }

public:
    int minDepth(TreeNode* root) {
        int result = getDepth(root);
        return result;
    }
};

class Solution1 {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int depth = 0;

        queue<TreeNode*> Nodes;
        Nodes.push(root);
        while(!Nodes.empty()) {
            int size = Nodes.size();
            depth += 1;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = Nodes.front();
                Nodes.pop();
                if (node->left) Nodes.push(node->left);
                if (node->right) Nodes.push(node->right);
                if (node->left == nullptr && node->right == nullptr) {
                    return depth;
                }
            }
        }
        return depth;

    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
