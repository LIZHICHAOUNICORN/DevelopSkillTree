#include <iostream>
#include <vector>
#include <stack>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using namespace std;
// https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list

// TowPointer. Time: O(n), Space: O(1)

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode dummy(0, head);
        ListNode* slow = &dummy;
        while (fast != nullptr) {
            int distence = 0;
            while (distence < n && fast != nullptr ) {
                fast = fast->next;
                distence += 1;
            }
            while (fast) {
                fast = fast->next;
                slow = slow->next;
            }
            slow->next = slow->next->next;
        }
        return dummy.next;
    }
};


int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> height({1,8,6,2,5});
  int ret = solu.maxArea(height);
  cout << ret << endl;
  
  return 0;
}
