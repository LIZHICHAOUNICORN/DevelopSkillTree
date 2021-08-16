#include <vector>
#include <stack>

#include "../Tree/tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  TreeNode* mergeTrees(TreeNode* tree1, TreeNode* tree2) {
    if (tree1 == nullptr) return tree2;
    if (tree2 == nullptr) return tree1;
    auto merged = new TreeNode(tree1->val, tree2->val);
    merged->left = mergeTrees(tree1->left, tree2->left);
    merged->rigth = mergeTrees(tree1->right, tree1->right);
    return merged;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
