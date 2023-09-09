#include <algorithm>
#include <map>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 private:
  int dfs(TreeNode* node, bool steal, int value) {
    if (node == nullptr) return value;

    int left = dfs(node->left, false, value);
    int right = dfs(node->right, false, value);
    if (steal) {
      value = left + right;
    } else {
      int l = dfs(node->left, true, value);
      int r = dfs(node->right, true, value);
      value = max(left + right, node->val + l + r);
    }
    return value;
  }

 public:
  int rob(TreeNode* root) {
    int value = 0;

    if (root == nullptr) return value;

    int s_value = dfs(root->left, true, value) + dfs(root->right, true, value) +
                  root->val;
    int ns_value =
        dfs(root->left, false, value) + dfs(root->right, false, value);
    return max(s_value, ns_value);
  }
};

// DFS
class Solution2 {
 public:
  int rob(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return root->val;
    // 偷父节点
    int val1 = root->val;
    if (root->left)
      val1 += rob(root->left->left) +
              rob(root->left->right);  // 跳过root->left，相当于不考虑左孩子了
    if (root->right)
      val1 += rob(root->right->left) +
              rob(root->right->right);  // 跳过root->right，相当于不考虑右孩子了
    // 不偷父节点
    int val2 = rob(root->left) + rob(root->right);  // 考虑root的左右孩子
    return max(val1, val2);
  }
};

// DFS + cache
class Solution3 {
 public:
  unordered_map<TreeNode*, int> umap;  // 记录计算过的结果
  int rob(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return root->val;
    if (umap[root]) return umap[root];  // 如果umap里已经有记录则直接返回
    // 偷父节点
    int val1 = root->val;
    if (root->left)
      val1 += rob(root->left->left) + rob(root->left->right);  // 跳过root->left
    if (root->right)
      val1 +=
          rob(root->right->left) + rob(root->right->right);  // 跳过root->right
    // 不偷父节点
    int val2 = rob(root->left) + rob(root->right);  // 考虑root的左右孩子
    umap[root] = max(val1, val2);                   // umap记录一下结果
    return max(val1, val2);
  }
};

// 树形DP
class Solution4 {
 public:
  int rob(TreeNode* root) {
    vector<int> result = robTree(root);
    return max(result[0], result[1]);
  }
  // 长度为2的数组，0：不偷，1：偷
  vector<int> robTree(TreeNode* cur) {
    if (cur == NULL) return vector<int>{0, 0};
    vector<int> left = robTree(cur->left);
    vector<int> right = robTree(cur->right);
    // 偷cur
    int val1 = cur->val + left[0] + right[0];
    // 不偷cur
    int val2 = max(left[0], left[1]) + max(right[0], right[1]);
    return {val2, val1};
  }
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
