#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

DEFINE_int32(reverse_input_size, 0, "input data size");

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

/*
    要在一遍内执行完的问题就是指针不能知道当前节点是倒数第几个，
    所以考虑用快慢指针。快指针比慢指针快n个节点，当快指针的下
    一个元素为空就说明慢指针的下一个节点应该删除。
*/
class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dmy = new ListNode(0);
    dmy->next = head;
    ListNode* tor = dmy;
    ListNode* hare = dmy;

    for (int i = 1; i <= n + 1; i++) {
      hare = hare->next;
    }

    while (hare != NULL) {
      hare = hare->next;
      tor = tor->next;
    }

    tor->next = tor->next->next;

    return dmy->next;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
