#ifndef LEETCODE_CREATE_LINKED_LIST_
#define LEETCODE_CREATE_LINKED_LIST_

#include "create_linked_list.h"

#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

ListNode* CreateLinkList(vector<int> vec) {
  if (vec.empty()) return nullptr;
  ListNode *head = new ListNode(vec[0]);
  ListNode *start = head;
  for (size_t it = 1; it < vec.size(); ++it) {
    ListNode* node = new ListNode(vec[it]);
    head->next = node;
    head = head->next;
  }
  return start;
}

void PrintLinkList(ListNode* head) {
  while (head != nullptr) {
    LOG(INFO) << head->val;
    head = head->next;
  }
}

void CleanLinkList(ListNode* head) {
  while (head != nullptr) {
    ListNode* next_node = head->next;
    delete head;
    head = next_node;
  }
}

#endif // LEETCODE_CREATE_LINKED_LIST_
