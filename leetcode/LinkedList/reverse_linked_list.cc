#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(reverse_input_size, 0, "input data size");

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if(head == nullptr) return head;
    ListNode* cur = head;
    ListNode* temp = nullptr;
    ListNode* pre = nullptr;
    while (cur != nullptr) {
      temp = cur->next;
      cur->next = pre;
      pre = cur;
      cur = temp;
    }
    return pre;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
