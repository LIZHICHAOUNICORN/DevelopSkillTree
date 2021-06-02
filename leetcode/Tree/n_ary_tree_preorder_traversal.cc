#include <vector>
#include <stack>
#include <algorithm>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<int> preorder(Node* root) {
    vector<int> ret;
    if (root == nullptr) return ret;
    helper(root, ret);
    return ret;
  }
 private:
  void helper(Node* cur, vector<int>& ret) {
    if (cur == nullptr) return;
    ret.push_back(cur->val);
    for (size_t i = 0; i < cur->children.size(); ++i) {
      if (cur->children[i] == nullptr) continue;
      helper(cur->children[i], ret);
    }
  }
};


class Solution1 {
 public:
  vector<int> preorder(Node* root) {
    vector<int> ret;
    if (root == nullptr) return ret;
    stack<Node*> reserve;
    reserve.push(root);
    Node* cur = nullptr;
    while (!reserve.empty()) {
      cur = reserve.top();
      reserve.pop();
      if (cur != nullptr) {
        ret.emplace_back(cur->val);
      } else {
        continue;
      }
      if (cur->children.empty()) continue;
      int size = cur->children.size();
      for (int i = size - 1; i >= 0; --i) {
        if (cur->children[i] == nullptr) continue;
        reserve.push(cur->children[i]);
      }
    }
    return ret;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
