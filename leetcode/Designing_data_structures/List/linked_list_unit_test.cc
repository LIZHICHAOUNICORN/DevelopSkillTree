#include <gflags/gflags.h>
#include <glog/logging.h>

#include "leetcode/Designing_data_structures/List/double_linked_list.h"

// using namespace base;

struct DemoNode {
  int key;
  struct base::list_head list;
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  struct base::list_head head, head2;
  INIT_LIST_HEAD(&head);
  INIT_LIST_HEAD(&head2);

  struct DemoNode* node;
  for (int i = 0; i < 10; ++i) {
    node = new struct DemoNode;
    node->key = i;
    base::list_add(&node->list, &head);
    LOG(INFO) << "head:  " << &head << ", add list " << node;
  }

  for (int i = 10; i < 20; i++) {
    node = new struct DemoNode;
    node->key = i;
    list_add(&node->list, &head2);
    LOG(INFO) << "head:  " << &head2 << ", add list " << node;
  }

  struct base::list_head* pos;
  list_for_each(pos, &head) {
    struct DemoNode* node = list_entry(pos, struct DemoNode, list);
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }

  list_for_each_prev(pos, &head) {
    struct DemoNode* node = list_entry_ptr(pos, typeof(node), list);
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }

  list_for_each_entry(node, &head, list) {
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }
  // mtf & mao
  list_mtf(head.next->next, &head);  // 2nd element
  list_for_each_entry(node, &head, list) {
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }
  list_mao(head.next->next->next, &head);  // 3rd element
  list_for_each_entry(node, &head, list) {
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }

  list_move(head.next, &head2);
  list_for_each_entry(node, &head, list) {
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }

  list_for_each_entry(node, &head2, list) {
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }

  list_splice_init(&head, &head2);
  list_for_each_entry(node, &head2, list) {
    LOG(INFO) << "node :" << node << ", key: " << node->key;
  }

  struct DemoNode* n;
  list_for_each_entry_safe(node, n, &head, list) {
    list_del(&node->list);
    LOG(INFO) << "node :" << node << ", key: " << node->key;
    free(node);
  }
  list_for_each_entry_safe(node, n, &head2, list) {
    list_del(&node->list);
    LOG(INFO) << "node :" << node << ", key: " << node->key;
    free(node);
  }
  return 0;
}
