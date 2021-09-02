#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

// Problem: https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head;
        ListNode* slow = head;
        
        while (k > 0 && fast != nullptr) {
            fast = fast->next;
            k -= 1;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;

    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
