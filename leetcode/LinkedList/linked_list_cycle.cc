#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution1 {
 public:
  bool hasCycle(ListNode *head) {
    unordered_set<ListNode *> seen;
    while (head != nullptr) {
      if (seen.count(head)) {
        return true;
      }
      seen.insert(head);
      head = head->next;
    }
    return false;
  }
};
class Solution {
 public:
  bool HasCycle(ListNode *head) {
    if (head == nullptr) return false;
    if (head->next == nullptr) return false;
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != slow && fast != nullptr) {
      slow = slow->next;
      fast = fast->next;
      if (fast == nullptr) continue;
      fast = fast->next;
    }
    return fast != nullptr;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
