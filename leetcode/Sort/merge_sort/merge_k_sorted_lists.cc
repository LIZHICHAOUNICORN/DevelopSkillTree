#include <algorithm>
#include <cstdlib>
#include <random>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/merge-k-sorted-lists/

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

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

class Solution1 {
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

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<ListNode*> lists({nullptr});

  Solution solu;
  auto ret = solu.mergeKLists(lists);
  LOG(INFO) << ret;
  return 0;
}
