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
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
 public:
  Node* connect(Node* root) {
    queue<Node*> Nodes;
    if (root != nullptr) Nodes.push(root);
    while (!Nodes.empty()) {
      int size = Nodes.size();
      Node* cur = nullptr;
      Node* pre = nullptr;
      for (int i = 0; i < size; ++i) {
        if (i == 0) {
          pre = Nodes.front();
          Nodes.pop();
          cur = pre;
        } else {
          cur = Nodes.front();
          Nodes.pop();
          pre->next = cur;
          pre = cur;
        }
        if (cur->left) Nodes.push(cur->left);
        if (cur->right) Nodes.push(cur->right);
      }
    }
    return root;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
