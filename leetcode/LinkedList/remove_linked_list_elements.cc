#include "glog/logging.h"
#include "gflags/gflags.h"

#include "create_linked_list.h"

using namespace std;

class Solution {
 public:
  ListNode* removeElements(ListNode* head, int val) {
    if (head == nullptr){
      return head;
    }
    ListNode* p=head;
    while (p->next != nullptr ){
      if (p->next->val == val){
        p->next = p->next->next;
      } else {
        p=p->next;
      }
    }
    if (head->val==val) {
      head=head->next;
    }
    return head;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int val = 6;
  Solution solu;
  solu.removeElements(nullptr, val);
  return 0;
}
