#include <stack>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/merge-k-sorted-lists/
// Solution:
// https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/he-bing-kge-pai-xu-lian-biao-by-leetcode-solutio-2/

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
  ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    if ((!a) || (!b)) return a ? a : b;
    ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
    while (aPtr && bPtr) {
      if (aPtr->val < bPtr->val) {
        tail->next = aPtr;
        aPtr = aPtr->next;
      } else {
        tail->next = bPtr;
        bPtr = bPtr->next;
      }
      tail = tail->next;
    }
    tail->next = (aPtr ? aPtr : bPtr);
    return head.next;
  }

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode* ans = nullptr;
    for (size_t i = 0; i < lists.size(); ++i) {
      ans = mergeTwoLists(ans, lists[i]);
    }
    return ans;
  }
};

class Solution1 {
 public:
  ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    if ((!a) || (!b)) return a ? a : b;
    ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
    while (aPtr && bPtr) {
      if (aPtr->val < bPtr->val) {
        tail->next = aPtr;
        aPtr = aPtr->next;
      } else {
        tail->next = bPtr;
        bPtr = bPtr->next;
      }
      tail = tail->next;
    }
    tail->next = (aPtr ? aPtr : bPtr);
    return head.next;
  }

  ListNode* merge(vector<ListNode*>& lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = (l + r) >> 1;
    return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
  }

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size() - 1);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  auto ptr = solu.mergeTwoLists(nullptr, nullptr);
  LOG(INFO) << ptr;

  return 0;
}
