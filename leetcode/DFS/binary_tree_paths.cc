#include <vector>
#include <stack>

#include "../Tree/tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> vec_ret;
    if (root == NULL) return vec_ret;
    string s;
    GetTreePaths(vec_ret, s, root);
    
    return vec_ret;
  }
  void GetTreePaths(vector<string> &vec_ret, string s, TreeNode *root) {
    if (root == NULL) return;
    
    s += to_string(root->val);
    if (root->left == NULL && root->right == NULL) { //the current node is leaf,then put s into vec_ret
        vec_ret.push_back(s);
    }
    else {
        s += "->";
    }

    GetTreePaths(vec_ret, s, root->left);//recur in left subtree
    GetTreePaths(vec_ret, s, root->right);//recur in right subtree
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
