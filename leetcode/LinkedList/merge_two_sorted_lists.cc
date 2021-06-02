#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

#include "create_linked_list.h"

using namespace std;

class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    ListNode* head = nullptr, *cur = nullptr;
    if (l1->val > l2->val) {
      head = l2;
      l2 = l2->next;
    } else {
      head = l1;
      l1 = l1->next;
    }
    cur = head;
    for ( ;l1 != nullptr && l2 != nullptr; ) {
      if (l1 != nullptr && l2 != nullptr) {
        if (l1->val > l2->val) {
          cur->next = l2;
          l2 = l2->next;
          cur = cur->next;
        } else {
          cur->next = l1;
          l1 = l1->next;
          cur = cur->next;
        }
        continue;
      }
    }
    if (l1 != nullptr) cur->next = l1;
    if (l2 != nullptr) cur->next = l2;
    return head;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1,2,3,4,5,6};
  vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  return 0;
}
