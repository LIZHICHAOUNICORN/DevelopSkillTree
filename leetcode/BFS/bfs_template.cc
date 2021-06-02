// Author: zhichaoli
// Time: 2020年02月12日

#include <set>
#include <stack>
#include <queue>

#include "../Tree/tree_node.h"
#include "glog/logging.h"
#include "gflags/gflags.h"

using std::set;
using std::queue;

// loop
void bfs_loop(TreeNode* root) {
  if (root == nullptr) return;
  queue<TreeNode*> node;
  set<TreeNode*> visited;
  node.push(root);
  while (!node.empty()) {
    TreeNode* cur = node.back();
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
