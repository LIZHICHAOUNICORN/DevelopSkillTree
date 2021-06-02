#include <random>
#include <vector>

#include "create_linked_list.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(reverse_input_size, 0, "input data size");

using namespace std;

class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0);
    ListNode* dummy_ptr = &dummy;
    ListNode* pre = dummy_ptr;
    dummy_ptr->next = head;
    size_t len = Length(head);
    for (size_t i = 0; i < len / k; ++i) {
      for (size_t j = 1; j < k; ++j) {
        ListNode* temp = pre->next;
        pre->next = head->next;
        head->next = head->next->next;
        pre->next->next = temp;
      }
      pre = head;
      head = head->next;
    }
    return dummy_ptr->next;
  }
 private:
  size_t Length(ListNode* head) {
    size_t len = 0;
    while (head != nullptr) {
      len++;
      head = head->next;
    }
    return len;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1,2,3,4,5};
  vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  ListNode* head = CreateLinkList(input_value);
  Solution solu;
  ListNode* ret = solu.reverseKGroup(head, 2);
  PrintLinkList(ret);
  CleanLinkList(ret);
  return 0;
}
