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
// 双指针
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

// 暴力解法
class Solution {
public:
    int getLength(ListNode* head) {
        int length = 0;
        while (head) {
            ++length;
            head = head->next;
        }
        return length;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        int length = getLength(head);
        ListNode* cur = dummy;
        for (int i = 1; i < length - n + 1; ++i) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
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
