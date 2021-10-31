#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/reverse-linked-list-ii/
// Solution:
// https://leetcode-cn.com/problems/reverse-linked-list-ii/solution/java-shuang-zhi-zhen-tou-cha-fa-by-mu-yi-cheng-zho/

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
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    // 定义一个dummyHead, 方便处理
    ListNode dummyHead = ListNode(0);
    dummyHead.next = head;

    // 初始化指针
    ListNode* g = &dummyHead;
    ListNode* p = dummyHead.next;

    // 将指针移到相应的位置
    for (int step = 0; step < left - 1; step++) {
      g = g->next;
      p = p->next;
    }

    // 头插法插入节点
    for (int i = 0; i < right - left; i++) {
      ListNode* removed = p->next;
      p->next = p->next->next;

      removed->next = g->next;
      g->next = removed;
    }

    return dummyHead.next;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
