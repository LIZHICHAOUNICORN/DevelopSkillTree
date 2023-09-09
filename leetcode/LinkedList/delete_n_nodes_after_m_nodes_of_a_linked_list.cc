#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* deleteNodes(ListNode* head, int m, int n) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode dummy(-1, head);
    ListNode* cur = dummy.next;
    int m_cn = 1;
    int n_cn = 0;
    while (cur) {
      // m step save
      while (cur && m_cn < m) {
        cur = cur->next;
        m_cn += 1;
      }
      m_cn = 1;
      if (cur == nullptr) break;
      ListNode* rm_node = cur->next;
      // n step skip
      while (rm_node && n_cn < n) {
        rm_node = rm_node->next;
        n_cn += 1;
      }
      n_cn = 0;
      cur->next = rm_node;

      if (rm_node) {
        cur = cur->next;
      } else {
        break;
      }
    }
    return dummy.next;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
