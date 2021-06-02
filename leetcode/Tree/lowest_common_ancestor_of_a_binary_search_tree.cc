#include <vector>
#include <stack>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if ((root -> val > p -> val) && (root -> val > q -> val)) {
      return lowestCommonAncestor(root -> left, p, q);
    }
    if ((root -> val < p -> val) && (root -> val < q -> val)) {
      return lowestCommonAncestor(root -> right, p, q);
    }
    return root;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  solu.lowestCommonAncestor(nullptr, nullptr, nullptr);
  return 0;
}
