#include <vector>
#include <queue>
#include <algorithm>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    if(!root) return {};
    vector<vector<int>> ans;
    queue<Node*> que;
    que.push(root);
    while(!que.empty()) {
      vector<int> v;
      for(int i=que.size();i;i--) {
          //压入当前层
        Node* curr=que.front();
        que.pop();
        v.push_back(curr->val);
        for(Node* it:curr->children) {
          que.push(it);
        }
      }
      ans.push_back(v);
    }
    return ans;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  
  return 0;
}
