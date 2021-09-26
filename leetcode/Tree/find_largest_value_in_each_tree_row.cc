#include <stack>
#include <vector>

#include "./tree_node.h"

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
 public:
  vector<int> largestValues(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;

    queue<TreeNode*> Nodes;
    Nodes.push(root);
    while (!Nodes.empty()) {
      int size = Nodes.size();
      int max = INT_MIN;
      for (int i = 0; i < size; ++i) {
        TreeNode* node = Nodes.front();
        Nodes.pop();
        if (max < node->val) {
          max = node->val;
        }
        if (node->left) Nodes.push(node->left);
        if (node->right) Nodes.push(node->right);
      }
      ans.push_back(max);
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
