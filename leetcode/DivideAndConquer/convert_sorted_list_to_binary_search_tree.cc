#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 private:
  ListNode* FindMiddle(ListNode* left, ListNode* right) {
    ListNode* fast = left;
    ListNode* slow = left;
    while (fast != right && fast->next != right) {
      fast = fast->next;
      fast = fast->next;
      slow = slow->next;
    }
    return slow;
  }
  TreeNode* BuildTree(ListNode* start, ListNode* end) {
    if (start == end) return nullptr;

    ListNode* mid = FindMiddle(start, end);
    TreeNode* cur = new TreeNode(mid->val);

    cur->left = BuildTree(start, mid);
    cur->right = BuildTree(mid->next, end);

    return cur;
  }

 public:
  TreeNode* sortedListToBST(ListNode* head) { return BuildTree(head, nullptr); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  TreeNode* ret = solu.sortedListToBST(nullptr);
  LOG(INFO) << "result: " << ret;
  return 0;
}
