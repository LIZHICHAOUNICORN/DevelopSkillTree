#include <stack>
#include <vector>

#include "./tree_node.h"

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> ans;
    if (root == nullptr) return ans;

    queue<Node*> Nodes;
    Nodes.push(root);
    while (!Nodes.empty()) {
      int size = Nodes.size();
      vector<int> level_result;
      for (int i = 0; i < size; ++i) {
        Node* node = Nodes.front();
        Nodes.pop();
        level_result.push_back(node->val);
        for (int j = 0; j < node->children.size(); ++j) {
          if (node->children[j]) Nodes.push(node->children[j]);
        }
      }
      ans.push_back(level_result);
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
