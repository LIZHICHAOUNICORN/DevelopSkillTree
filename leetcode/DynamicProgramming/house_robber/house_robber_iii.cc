#include <map>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::map;
using std::max;


struct TreeNode {
   int val;
   TreeNode* left;
   TreeNode* right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  int rob(TreeNode* root) {
  if (root == nullptr) return 0;
  if (cache[root]) return cache[root];
  // 对根抢劫
  int do_it = root->val +
              (root->left == nullptr ? 0 : rob(root->left->left) + rob(root->left->right)) +
              (root->right == nullptr ? 0 : rob(root->right->left) + rob(root->right->right));


  // 对根不抢
  int not_do = rob(root->left) + rob(root->right);
  int ret = max(do_it, not_do);
  cache[root] = ret;
  return ret;

  }

 private:
  map<TreeNode*, int> cache;
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  TreeNode root(3);
  Solution solu;
  int ret = solu.rob(&root);
  LOG(INFO) << ret;
  return 0;
}
