// Author: zhichaoli
// Time: 2020年02月12日

#include <set>
#include <stack>

#include "../Tree/tree_node.h"
#include <gflags/gflags.h>
#include <glog/logging.h>

using std::set;
using std::stack;

// Recursion
void dfs(TreeNode* node_ptr, set<TreeNode*>& visited) {
  if (visited.find(node_ptr) != visited.end()) {
    return;
  }
  visited.insert(node_ptr);
  // iterator node chidrens
  dfs(node_ptr->left, visited);
  dfs(node_ptr->right, visited);
}
// loop
void dfs_loop(TreeNode* root) {
  if (root == nullptr) return;
  stack<TreeNode*> node;
  set<TreeNode*> visited;
  node.push(root);
  while (!node.empty()) {
    TreeNode* cur = node.top();
    node.pop();
    // process cur
    // new_nodes = generate_nodes(node)
    // stack.push(new_nodes);
  }
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
