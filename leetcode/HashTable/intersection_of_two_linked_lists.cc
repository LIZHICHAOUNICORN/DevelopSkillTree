#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// time O(m+n), space O(m)
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> cache;
        ListNode *a_copy = headA;
        while (a_copy != nullptr) {
            cache.insert(a_copy);
            a_copy = a_copy->next;
        }
        ListNode* b_copy = headB;
        while (b_copy != nullptr) {
            if (cache.count(b_copy)) {
                return b_copy;
            }
            b_copy = b_copy->next;
        }
        return nullptr;
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
