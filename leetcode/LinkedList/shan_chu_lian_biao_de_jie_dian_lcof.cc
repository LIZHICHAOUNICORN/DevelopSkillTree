#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/

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
  ListNode* deleteNode(ListNode* head, int val) {
    ListNode dummy(-1, head);
    ListNode* cur = &dummy;
    while (
        cur->next)  //由于即使head为空，cur初始值也不为空，所以该循环不会报错。
    {
      if (cur->next->val == val) {
        cur->next = cur->next->next;
        /*找到需要删除的节点后，进行常规删除操作。
        *此时cur->next需要被删除，所以只需改变cur节点的next指针即可。
        */
        break;
        //只删除一个节点，找到删除该节点之后，无需再遍历，节省时间
      }
      cur = cur->next;  // cur节点要不断往后走，才能进行链表的遍历。
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
