#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/split-linked-list-in-parts/

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  vector<ListNode *> splitListToParts(ListNode *head, int k) {
    int n = 0;
    ListNode *temp = head;
    while (temp != nullptr) {
      n++;
      temp = temp->next;
    }
    int quotient = n / k, remainder = n % k;

    vector<ListNode *> parts(k, nullptr);
    ListNode *curr = head;
    for (int i = 0; i < k && curr != nullptr; i++) {
      parts[i] = curr;
      int partSize = quotient + (i < remainder ? 1 : 0);
      for (int j = 1; j < partSize; j++) {
        curr = curr->next;
      }
      ListNode *next = curr->next;
      curr->next = nullptr;
      curr = next;
    }
    return parts;
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
