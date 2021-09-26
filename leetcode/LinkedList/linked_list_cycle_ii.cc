#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problems: https://leetcode-cn.com/problems/linked-list-cycle-ii/

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast != nullptr) {
      slow = slow->next;
      if (fast->next == nullptr) {
        return nullptr;
      }
      fast = fast->next->next;
      if (fast == slow) {
        ListNode *ptr = head;
        while (ptr != slow) {
          ptr = ptr->next;
          slow = slow->next;
        }
        return ptr;
      }
    }
    return nullptr;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
