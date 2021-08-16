#include <vector>
#include <stack>

// #include "../Tree/tree_node.h"

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
};

class Solution {
 public:
   int ans;
   int depth(TreeNode* node) {
     if (node == nullptr) {
       return 0;
     }
     int l = depth(node->left);
     int r = depth(node-right);
     ans = max(ans, l+r+1);
     return max(l, r)+1;
   }
   int diameterOfBinaryTree(TreeNode* root) {
     ans = 1;
     depth(root);
     return ans-1;
   }
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
