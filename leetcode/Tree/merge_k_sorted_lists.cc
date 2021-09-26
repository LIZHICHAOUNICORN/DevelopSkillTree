#include <vector>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 方法一：暴力方法。先sort,再组合，时间复杂度：O(nlogn), 空间复杂度：O(n)
class Solution {
 private:
  static bool cmp(ListNode*& a, ListNode*& b) { return a->val < b->val; }

 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    vector<ListNode*> arr;
    for (int i = 0; i < lists.size(); i++) {
      ListNode* head = lists[i];
      while (head != nullptr) {
        arr.push_back(head);
        head = head->next;
      }
    }
    sort(arr.begin(), arr.end(), cmp);
    ListNode node(0, nullptr);
    ListNode* cur = &node;
    for (int i = 0; i < arr.size(); i++) {
      cur->next = arr[i];
      cur = cur->next;
    }
    // 注意，必须在最后nullptr.
    cur->next = nullptr;
    return node.next;
  }
};

// 方法二：暴力方法 进阶优化：时间复杂度：O(n*logn) 空间复杂度：O(n)
class Solution {
 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto head = ListNode(0, nullptr);
    auto comp = [](ListNode* const& a, ListNode* const& b) {
      return a->val > b->val;
    };
    priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> q(comp);
    for (auto& h : lists)
      if (h != nullptr) q.push(h);
    auto p = &head;
    while (!q.empty()) {
      p->next = q.top();
      q.pop();
      p = p->next;
      if (p->next != nullptr) q.push(p->next);
    }
    return head.next;
  }
};

// 方法三：暴力方法：依次合并两个链表。时间复杂度：O(k^2*n).空间复杂度：O(1)：k:
// 链表个数，n:链表平均长度
class Solution {
 private:
  ListNode* mergeTwoLists(ListNode* left, ListNode* right) {
    if (left == nullptr || right == nullptr) {
      return left == nullptr ? right : left;
    }
    ListNode node(0, nullptr);
    ListNode* pre = &node;
    while (left != nullptr && right != nullptr) {
      if (left->val > right->val) {
        pre->next = right;
        right = right->next;
      } else {
        pre->next = left;
        left = left->next;
      }
      pre = pre->next;
    }
    pre->next = left != nullptr ? left : right;
    return node.next;
  }

 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode* result = nullptr;
    for (size_t i = 0; i < lists.size(); ++i) {
      result = mergeTwoLists(result, lists[i]);
    }
    return result;
  }
};

// 方法四：分治合并。 时间复杂度： O(kn×logk), 空间复杂度：O(logk)。k:
// 链表个数，n:链表平均长度
class Solution {
 private:
  ListNode* mergeTwoLists(ListNode* left, ListNode* right) {
    if (left == nullptr || right == nullptr) {
      return left == nullptr ? right : left;
    }
    ListNode node(0, nullptr);
    ListNode* pre = &node;
    while (left != nullptr && right != nullptr) {
      if (left->val > right->val) {
        pre->next = right;
        right = right->next;
      } else {
        pre->next = left;
        left = left->next;
      }
      pre = pre->next;
    }
    pre->next = left != nullptr ? left : right;
    return node.next;
  }
  ListNode* merge(vector<ListNode*>& lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = l + (r - l) / 2;
    return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
  }

 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size() - 1);
  }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
