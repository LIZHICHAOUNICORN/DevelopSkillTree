#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/copy-list-with-random-pointer/
// Solution:
// https://leetcode-cn.com/problems/copy-list-with-random-pointer/solution/fu-zhi-dai-sui-ji-zhi-zhen-de-lian-biao-c2nvs/

using namespace std;

// Definition for singly-linked list.
struct Node {
  int val;
  Node* next;
  Node* random;
  Node(int x) : val(x), next(NULL), random(NULL) {}
};

class Solution {
 public:
  Node* copyRandomList(Node* head) {
    for (auto p = head; p;
         p = p->next->next)  //复制每个节点，并将原链表和复制链表连在一起。
    {
      auto q = new Node(p->val);
      q->next = p->next;
      p->next = q;
    }

    for (auto p = head; p; p = p->next->next)  //复制random指针
    {
      if (p->random) p->next->random = p->random->next;
    }

    //拆分两个链表，并复原原链表
    auto dummy = new Node(-1), cur = dummy;
    for (auto p = head; p; p = p->next) {
      auto q = p->next;
      cur = cur->next = q;
      p->next = q->next;
    }

    return dummy->next;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
