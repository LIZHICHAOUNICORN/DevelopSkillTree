#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem:
// https://leetcode-cn.com/problems/linked-list-cycle/

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  bool hasCycle(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return false;
    }
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (slow != fast) {
      if (fast == nullptr || fast->next == nullptr) {
        return false;
      }
      slow = slow->next;
      fast = fast->next->next;
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  bool ret = solu.hasCycle(nullptr);
  LOG(INFO) << ret;

  return 0;
}
