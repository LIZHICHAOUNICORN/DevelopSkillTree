#include <stack>
#include <vector>

#include "./tree_node.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

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
  vector<double> averageOfLevels(TreeNode* root) {
    vector<double> ret;
    if (root == nullptr) return ret;
    queue<TreeNode*> Nodes;
    Nodes.push(root);
    while (!Nodes.empty()) {
      int size = Nodes.size();
      double avg = 0;
      for (int i = 0; i < size; ++i) {
        TreeNode* node = Nodes.front();
        Nodes.pop();
        avg += node->val;
        if (node->left) Nodes.push(node->left);
        if (node->right) Nodes.push(node->right);
      }
      ret.push_back(avg / size);
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
