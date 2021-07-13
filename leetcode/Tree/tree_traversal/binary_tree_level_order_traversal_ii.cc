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
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return ans;

        queue<TreeNode*> Nodes;
        Nodes.push(root);
        while (!Nodes.empty()) {
            int size = Nodes.size();
            vector<int> level_result;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = Nodes.front();
                Nodes.pop();
                level_result.push_back(node->val);
                if (node->left) Nodes.push(node->left);
                if (node->right) Nodes.push(node->right);
            }
            ans.push_back(level_result);
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
