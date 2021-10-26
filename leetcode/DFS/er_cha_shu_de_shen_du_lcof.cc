#include <algorithm>
#include <climits>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof/

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 private:
  int dfs(TreeNode *node, int h) {
    if (node == nullptr) return h;
    return max(dfs(node->left, h + 1), dfs(node->right, h + 1));
  }

 public:
  int maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    return max(dfs(root->left, 1), dfs(root->right, 1));
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.maxDepth(nullptr);
  LOG(INFO) << ret;
  return 0;
}
