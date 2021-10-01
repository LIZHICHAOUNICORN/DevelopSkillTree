# Linked-List
## 分类
### 单链表
### 双向链表

## 实现
```cpp
// 单链表节点实现
struct ListNode {
   int val; // 链表值
   ListNode *next;  // 下一个节点
   ListNode(int x) : val(x), next(nullptr) {}  // 构造函数
};
```

## 基本操作
### 构造链表
### 查找
查找特定节点，只能通过遍历，这个操作的复杂度是O(n).
### 删除
删除特定节点复杂度是O(1)，在进行链表删除节点的操作时，经常会因为对当前节点进行操作而导致内存或指针出现问题，有两个小技巧可以解决这个问题:
1. 尽量处理当前节点的下一个节点而非当前节点本身；
2. 是建立一个虚拟节点 (dummy node)，使其指向当前链表的头节点，这样即使原链表 所有节点全被删除，也会有一个 dummy 存在，返回 dummy->next 即可。

题目：
- [x] [83. remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
- [x] [1474. delete-n-nodes-after-m-nodes-of-a-linked-list](https://leetcode-cn.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/)
- [x] [0203. delete-middle-node-lcci/](https://leetcode-cn.com/problems/delete-middle-node-lcci/)
- [x] [剑指 Offer 18. delete-middle-node-lcci/](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

### 插入
### 排序
### 合并
### 反转


## 应用场景
## 练习
- [ ] 83. remove-duplicates-from-sorted-list
- [ ] 206. Reverse Linked List
- [ ] 21. Merge Two Sorted Lists 
- [ ] 24. Swap Nodes in Pairs 
- [ ] 160. Intersection of Two Linked Lists 
- [ ] 234. Palindrome Linked List
- [ ] 83. Remove Duplicates from Sorted List
- [ ] 328. Odd Even Linked List
- [ ] 19. Remove Nth Node From End of List
- [ ] 148. Sort List
