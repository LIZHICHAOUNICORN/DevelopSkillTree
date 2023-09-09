#include <vector>
#include <map>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/path-sum-iii/
// Solution:
// https://leetcode-cn.com/problems/path-sum-iii/solution/acmjin-pai-ti-jie-dfs-shu-shang-qian-zhu-zu3k/

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  map<int, int> mp;
  int target, ans;
  int pathSum(TreeNode *root, int targetSum) {
    target = targetSum;
    mp[0] = 1;
    dfs(root, 0);
    return ans;
  }

  void dfs(TreeNode *node, int sum) {
    if (node == NULL) return;
    sum += node->val;
    ans += mp[sum - target];
    if (mp.find(sum) != mp.end())
      mp[sum]++;
    else
      mp[sum] = 1;
    dfs(node->left, sum);
    dfs(node->right, sum);
    mp[sum]--;
  }
};

class Solution1 {
 public:
  int target, ans;
  int pathSum(TreeNode *root, int targetSum) {
    if (root == NULL) return 0;
    target = targetSum;
    dfs(root);
    return ans;
  }

  void dfs(TreeNode *node) {
    dfs2(node, 0);
    if (node->left != NULL) dfs(node->left);
    if (node->right != NULL) dfs(node->right);
  }

  void dfs2(TreeNode *node, int sum) {
    sum += node->val;
    if (sum == target) ++ans;
    if (node->left != NULL) dfs2(node->left, sum);
    if (node->right != NULL) dfs2(node->right, sum);
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  int ret = 0;
  return 0;
}
