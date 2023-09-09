#include <iostream>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
using std::string;

// Problem:
// https://leetcode-cn.com/problems/kth-node-from-end-of-list-lcci/

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  int kthToLast(ListNode* head, int k) {
    if (head == nullptr) return -1;
    ListNode* fast = head;
    ListNode* slow = head;
    int cnt = 0;
    while (fast && cnt < k) {
      fast = fast->next;
      cnt += 1;
    }
    // 链表长度不大于k
    if (fast == nullptr) {
      return cnt == k ? head->val : -1;
    }

    while (fast) {
      slow = slow->next;
      fast = fast->next;
    }
    return slow->val;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  int ret = solu.kthToLast(nullptr, 2);
  LOG(INFO) << ret;

  return 0;
}
