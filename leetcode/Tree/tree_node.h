#ifndef LEETCODE_TREE_TREE_NODE_H_
#define LEETCODE_TREE_TREE_NODE_H_

#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

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

#endif // LEETCODE_TREE_TREE_NODE_H_
