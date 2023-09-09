#include <random>
#include <vector>

// #include "leetcode/LinkedList/create_linked_list.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

// https://leetcode-cn.com/problems/reverse-nodes-in-k-group/solution/5fen-dai-ma-ji-jian-cdai-ma-by-fengziluo-ucsi/

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

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

class Solution1 {
 private:
  int GetLen(ListNode* node) {
    int cnt = 0;
    while (node) {
      node = node->next;
      cnt += 1;
    }
    return cnt;
  }

 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0, nullptr);
    ListNode* pre = &dummy;
    ListNode* next = nullptr;
    ListNode* cur = pre;
    pre->next = head;
    int cnt = GetLen(head);
    while (cnt >= k) {
      cur = pre->next;
      next = cur->next;
      for (int i = 1; i < k; ++i) {
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
        next = cur->next;
      }
      pre = cur;
      cnt -= k;
    }
    return dummy.next;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1, 2, 3, 4, 5};
  vector<int> input_value(array_value,
                          array_value + sizeof(array_value) / sizeof(int));

  Solution solu;
  ListNode* ret = solu.reverseKGroup(nullptr, 2);
  return 0;
}
