#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
 public:
  ListNode *deleteDuplicates(ListNode *head) {
    if (head == nullptr) return head;
    ListNode dummy(-1, head);

    int pre_val = dummy.next->val;
    ListNode *pre = dummy.next;

    ListNode *cur = dummy.next->next;
    while (cur) {
      // delate node;
      if (cur->val == pre_val) {
        while (cur && cur->val == pre_val) {
          cur = cur->next;
        }
        pre->next = cur;
      }

      pre = cur;
      if (cur) {
        pre_val = cur->val;
        cur = cur->next;
      }
    }

    return dummy.next;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
