#include <vector>
#include <stack>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ret;
    if (root == nullptr) return ret;
    vector<TreeNode*> cur;
    vector<TreeNode*> next;
    cur.push_back(root);
    while (!cur.empty()) {
      vector<int> level;
      for (auto it : cur) {
        level.push_back(it->val);
        if (it->left) next.push_back(it->left);
        if (it->right) next.push_back(it->right);
      }
      ret.push_back(level);
      cur = next;
      next.clear();
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  TreeNode* root = nullptr;
  solu.levelOrder(root);
  return 0;
}
