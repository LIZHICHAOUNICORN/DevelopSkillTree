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
  ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    bool flag = false;
    while(fast && fast->next){
      fast = fast->next->next;
      slow = slow->next;
      if(fast == slow){
        flag = true;
        break;
      }
    }
    if(!flag) return NULL;
    slow = head;
    while(slow != fast){
      slow = slow->next;
      fast = fast->next;
    }
    return slow;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
