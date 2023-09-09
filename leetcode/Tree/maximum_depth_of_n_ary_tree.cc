#include <stack>
#include <vector>

#include "./tree_node.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

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
  int maxDepth(Node* root) {
    if (root == nullptr) return 0;
    int result = 0;
    for (int i = 0; i < root->children.size(); ++i) {
      result = max(result, maxDepth(root->children[i]));
    }
    return result + 1;
  }
};

class Solution1 {
 public:
  int maxDepth(Node* root) {
    if (root == nullptr) return 0;
    queue<Node*> Nodes;
    Nodes.push(root);
    int depth = 0;
    while (!Nodes.empty()) {
      int size = Nodes.size();
      for (int i = 0; i < size; ++i) {
        Node* node = Nodes.front();
        Nodes.pop();
        for (int j = 0; j < node->children.size(); ++j) {
          if (node->children[j]) Nodes.push(node->children[j]);
        }
      }
      depth += 1;
    }
    return depth;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
