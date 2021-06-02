#include <vector>
#include <stack>

#include <limits.h>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
  
    if ((root->left == nullptr) && (root->right == nullptr)) {
      return 1;
    }
  
    int min_depth = INT_MAX;
    if (root->left != nullptr) {
      min_depth = min(minDepth(root->left), min_depth);
    }
    if (root->right != nullptr) {
      min_depth = min(minDepth(root->right), min_depth);
    }

    return min_depth + 1;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
