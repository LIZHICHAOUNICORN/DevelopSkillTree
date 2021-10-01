# Linked-List
## 分类
### 单链表
### 双向链表

## 实现
```cpp
// 单链表节点实现
#include <bits/stdc++.h>

using namespace std;

//定义一个结点模板
template<typename T>
struct Node {
	T data;
	Node *next;
	Node() : next(nullptr) {}
	Node(const T &d) : data(d), next(nullptr) {}
};

//删除 p 结点后面的元素
template<typename T>
void Remove(Node<T> *p) {
	if (p == nullptr || p->next == nullptr) {
		return;
	}
	auto tmp = p->next->next;
	delete p->next;
	p->next = tmp;
}

//在 p 结点后面插入元素
template<typename T>
void Insert(Node<T> *p, const T &data) {
	auto tmp = new Node<T>(data);
	tmp->next = p->next;
	p->next = tmp;
}

//遍历链表
template<typename T, typename V>
void Walk(Node<T> *p, const V &vistor) {
	while(p != nullptr) {
		vistor(p);
		p = p->next;
	}
}

int main() {
	auto p = new Node<int>(1);
	Insert(p, 2);
	int sum = 0;
	Walk(p, [&sum](const Node<int> *p) -> void { sum += p->data; });
	cout << sum << endl;
	Remove(p);
	sum = 0;
	Walk(p, [&sum](const Node<int> *p) -> void { sum += p->data; });
	cout << sum << endl;
	return 0;
}
```

## 基本操作
### 构造链表
### 查找
查找特定节点，只能通过遍历，这个操作的复杂度是O(n).
### 删除
删除特定节点复杂度是O(1)，在进行链表删除节点的操作时，经常会因为对当前节点进行操作而导致内存或指针出现问题，有两个小技巧可以解决这个问题:
1. 尽量处理当前节点的下一个节点而非当前节点本身；
2. 是建立一个虚拟节点 (dummy node)，使其指向当前链表的头节点，这样即使原链表 所有节点全被删除，也会有一个 dummy 存在，返回 dummy->next 即可。

```cpp
class Solution {
 public:
  ListNode* deleteNode(ListNode* head, int val) {
    ListNode dummy(-1, head);
    ListNode* cur = &dummy;
    //由于即使head为空，cur初始值也不为空，所以该循环不会报错。
    while (cur->next) {
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
```

题目：
- [x] [83. remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
- [x] [1474. delete-n-nodes-after-m-nodes-of-a-linked-list](https://leetcode-cn.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/)
- [x] [剑指 Offer 18. delete-middle-node-lcci/](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

### 插入
### 排序
### 合并
### 反转


## 应用场景
对比于数组

数组的优缺点：
优点：可以根据偏移实现快速的随机读写。
缺点：扩容，增删元素极慢。

链表：无法高效获取长度，无法根据偏移快速访问元素，但是可以快速插入和删除，所以更适合于频繁修改的场景。

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
