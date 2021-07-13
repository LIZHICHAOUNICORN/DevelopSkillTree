#include <vector>
#include <stack>

#include "./tree_node.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return ans;
        queue<TreeNode*> cur;
        cur.push(root);
        while (!cur.empty()) {
            vector<int> level_result;
            int size = cur.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* cur_node = cur.front();
                cur.pop();
                level_result.push_back(cur_node->val);
                if (cur_node->left) cur.push(cur_node->left);
                if (cur_node->right) cur.push(cur_node->right);
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
