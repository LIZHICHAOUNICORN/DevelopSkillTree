#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// don't upderstand
class Solution {
 public:
  ListNode *swapPairs(ListNode *head) {
    ListNode *dummy = new ListNode(0), *node;
    node = dummy;
    dummy->next = head;
    while (head && head->next) {
      ListNode *nxt = head->next;
      head->next = nxt->next;
      nxt->next = head;
      node->next = nxt;
      node = head;
      head = node->next;
    }
    return dummy->next;
  }
};

class Solution2 {
 public:
  ListNode *swapPairs(ListNode *head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) return head;
    ListNode *next = head->next;
    head->next = swapPairs(next->next);
    next->next = head;
    return next;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
