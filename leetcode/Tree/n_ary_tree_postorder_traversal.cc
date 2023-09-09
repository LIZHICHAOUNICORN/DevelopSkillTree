#include <algorithm>
#include <stack>
#include <vector>

#include "./tree_node.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  vector<int> postorder(Node* root) {
    vector<int> ret;
    if (root == nullptr) return ret;
    helper(root, ret);
    return ret;
  }

 private:
  void helper(Node* cur, vector<int>& ret) {
    if (cur == nullptr) return;
    for (size_t i = 0; i < cur->children.size(); ++i) {
      helper(cur->children[i], ret);
    }
    ret.push_back(cur->val);
  }
};

class Solution2 {
 public:
  vector<int> postorder(Node* root) {
    vector<int> ret;
    if (root == nullptr) return ret;
    stack<Node*> reserve;
    reserve.push(root);
    Node* cur = nullptr;
    while (!reserve.empty()) {
      cur = reserve.top();
      reserve.pop();
      ret.push_back(cur->val);
      for (size_t i = 0; i < cur->children.size(); ++i) {
        if (cur->children[i] == nullptr) continue;
        reserve.push(cur->children[i]);
      }
    }
    reverse(ret.begin(), ret.end());
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
