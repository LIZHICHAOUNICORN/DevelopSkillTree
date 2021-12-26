#include <stack>
#include <vector>
#include <limits.h>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem:
// https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
 private:
  void scale(vector<int>& nums, size_t sz) {
    if (nums.size() < sz) {
      while (nums.size() < sz) {
        nums.emplace_back(INT_MAX);
      }
    }
  }

  void dfs(TreeNode* node, vector<int>& nums, int index) {
    scale(nums, 2 * index + 3);

    if (node == nullptr) {
      nums[index] = INT_MAX;
      return;
    }

    if (node->left) {
      dfs(node->left, nums, index * 2 + 1);
    } else {
      // nums.resize(2*index+2);
      // scale(nums, 2*index+2);
      nums[index * 2 + 1] = INT_MAX;
    }

    if (node->right) {
      dfs(node->right, nums, index * 2 + 2);
    } else {
      // scale(nums, 2*index+3);
      // nums.resize(2*index+3);
      nums[index * 2 + 2] = INT_MAX;
    }
    nums[index] = node->val;
  }

  TreeNode* buildTree(const vector<int>& nums) {
    TreeNode* node = new TreeNode(nums[0]);
    vector<TreeNode*> nodes(nums.size(), nullptr);
    nodes[0] = node;
    for (int i = 0; i < nums.size(); ++i) {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      if (left < nums.size()) {
        if (nums[left] != INT_MAX) {
          nodes[i]->left = new TreeNode(nums[left]);
          nodes[left] = nodes[i]->left;
        } else {
          if (nodes[i] != nullptr) {
            nodes[i]->left = nullptr;
          }
        }
      }
      if (right < nums.size()) {
        if (nums[right] != INT_MAX) {
          nodes[i]->right = new TreeNode(nums[right]);
          nodes[right] = nodes[i]->right;
        } else {
          if (nodes[i] != nullptr) {
            nodes[i]->right = nullptr;
          }
        }
      }
    }
    return node;
  }

 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    string ret;
    if (root == nullptr) return ret;

    vector<int> tree;
    // post-order
    dfs(root, tree, 0);

    for (const int& num : tree) {
      if (num != INT_MAX) {
        ret += to_string(num);
        ret += "#";
      } else {
        ret += "Nan";
        ret += "#";
      }
    }
    return ret;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    if (data.empty()) return nullptr;

    vector<int> nums;
    for (int i = 0; i < data.size(); ++i) {
      int start = i;
      while (data[i] != '#') {
        ++i;
      }
      const string& sub = data.substr(start, i - start);
      if (sub != "Nan") {
        int num = std::stoi(sub);
        nums.emplace_back(num);
      } else {
        nums.emplace_back(INT_MAX);
      }
    }
    return buildTree(nums);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Codec codec;
  auto ptr = codec.serialize(nullptr);
  LOG(INFO) << ptr;

  return 0;
}
