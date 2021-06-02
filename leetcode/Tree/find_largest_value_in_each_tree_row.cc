#include <vector>
#include <stack>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<int> largestValues(TreeNode* root) {
    vector<int> ret;
    if (root == nullptr) return ret;
    vector<TreeNode*> cur;
    vector<TreeNode*> next;
    cur.push_back(root);
    while (!cur.empty()) {
      int max = cur[0]->val;
      for (size_t i = 0; i < cur.size(); ++i) {
        if (max < cur[i]->val) max = cur[i]->val;
        if (cur[i]->left) {
          next.push_back(cur[i]->left);
        }
        if (cur[i]->right) {
          next.push_back(cur[i]->right);
        }
      }
      ret.push_back(max);
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
  solu.largestValues(root);
  return 0;
}
