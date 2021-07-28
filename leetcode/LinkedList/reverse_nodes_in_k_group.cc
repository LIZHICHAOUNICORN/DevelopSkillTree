#include <random>
#include <vector>

#include "create_linked_list.h"

#include "glog/logging.h"
#include "gflags/gflags.h"

DEFINE_int32(reverse_input_size, 0, "input data size");

using namespace std;

class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0);
    ListNode* dummy_ptr = &dummy;
    ListNode* pre = dummy_ptr;
    dummy_ptr->next = head;
    size_t len = Length(head);
    for (size_t i = 0; i < len / k; ++i) {
      for (size_t j = 1; j < k; ++j) {
        ListNode* temp = pre->next;
        pre->next = head->next;
        head->next = head->next->next;
        pre->next->next = temp;
      }
      pre = head;
      head = head->next;
    }
    return dummy_ptr->next;
  }
 private:
  size_t Length(ListNode* head) {
    size_t len = 0;
    while (head != nullptr) {
      len++;
      head = head->next;
    }
    return len;
  }
};

// https://leetcode-cn.com/problems/reverse-nodes-in-k-group/solution/5fen-dai-ma-ji-jian-cdai-ma-by-fengziluo-ucsi/
class Solution1 {
private:
    int GetLen(ListNode* node) {
        int cnt = 0;
        while (node) {
            node = node->next;
            cnt += 1;
        }
        return cnt;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, nullptr);
        ListNode* pre = &dummy;
        ListNode* next = nullptr;
        ListNode* cur = pre;
        pre->next = head;
        int cnt = GetLen(head);
        while (cnt >= k) {
            cur = pre->next;
            next = cur->next;
            for (int i = 1; i < k; ++i) {
                cur->next = next->next;
                next->next = pre->next;
                pre->next = next;
                next = cur->next;
            }
            pre = cur;
            cnt -= k;
        }
        return dummy.next;
    }
};


class Solution {
public:
    // 翻转一个子链表，并且返回新的头与尾
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail) {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* hair = new ListNode(0);
        hair->next = head;
        ListNode* pre = hair;

        while (head) {
            ListNode* tail = pre;
            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    return hair->next;
                }
            }
            ListNode* nex = tail->next;
            // 这里是 C++17 的写法，也可以写成
            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
            // head = result.first;
            // tail = result.second;
            tie(head, tail) = myReverse(head, tail);
            // 把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }

        return hair->next;
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1,2,3,4,5};
  vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  ListNode* head = CreateLinkList(input_value);
  Solution solu;
  ListNode* ret = solu.reverseKGroup(head, 2);
  PrintLinkList(ret);
  CleanLinkList(ret);
  return 0;
}
