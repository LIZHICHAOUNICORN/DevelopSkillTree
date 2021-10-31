#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/inorder-successor-in-bst-ii/

class Node {
 public:
  int val;
  Node* left;
  Node* right;
  Node* parent;
};

class Solution {
 public:
  Node* inorderSuccessor(Node* node) {
    // the successor is somewhere lower in the right subtree
    if (node->right) {
      node = node->right;
      while (node->left) node = node->left;
      return node;
    }

    // the successor is somewhere upper in the tree
    while (node->parent && node == node->parent->right) node = node->parent;
    return node->parent;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  Node* node = solu.inorderSuccessor(nullptr);
  return 0;
}
