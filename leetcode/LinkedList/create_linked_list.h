#include <vector>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* CreateLinkList(vector<int> vec);
void PrintLinkList(ListNode* head);
void CleanLinkList(ListNode* head);
