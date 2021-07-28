# Algorithms and Data Structures


## Trie and Disjoint set（字典树与并查集）

### Trie（字典树）

- #### 数据结构
1. BST（二叉搜索树）性质：有序， 左 < 根 < 右， 对于子树同样成立。

2. BST的遍历： 先序(pre-order)，中序(有序)(in-order)，后序(post-order) 。具体代码实现见/leetcode/Tree (TODO)

3. Trie（字典树）：与BST一样都是树，但是是多叉树。

4. Trie 主要应用场景：
4.1  用于统计大量字符串，经常被搜索引擎系统用于文本统计。
5. 优点：最大限度减少无谓的字符串比较，查询效率比hash高
- #### 核心思想
1. 空间换时间，利用字符串的公共前缀来降低时间的开销，进而提高效率。
- #### 性质
1. 节点本身不存储完整的单词。
2. 从根节点到某一节点，路径上经过的字符串连接起来，为该节点对应的字符串。
3. 每个节点的所有子节点路径代表的字符都不相同。
- #### TODO
**实现Trie 以及 分析srilm的Trie使用。**


### DoubleArrayTrie（双数组字典树）
- #### TODO
**实现DAT 以及 分析Hanlp中DAT实现**



### Disjoint set （并查集）
- #### 应对问题
组团配对问题
- #### 基本操作
1.  makesets(x) 	// 创建set
2.  unionset(x, y)		// 合并set x 和set y
3.  find(x)		// 查找 元素x所在 set
- #### 技巧
路径压缩

- #### TODO
**补充路径压缩技巧**


## Advanced Search（高级搜索）
- #### Prune（剪枝）
- #### Bidirectional  BFS（双向宽度有限搜索 ）
- #### Heuristic Search （启发式搜索）


## AVL Tree and Red-black Tree

### AVL Tree
- #### 为什么需要AVL Tree
- #### AVL Tree 如何保证平衡
- #### AVL Tree 总结

### Red-black Tree

- #### 为什么需要Reb-black Tree
- #### Reb-black Tree 性质

## 位运算
- #### 位运算符及特点

位运算符  | 操作说明
------------- | -------------
&  | 按位与
~  | 按位取反 
^  | 按位取异或
l    | 按位与或

	X^0 = X
	X^1s = ~X  // 注意1s = ~0
	


- #### 算术移位与逻辑移位
- #### 指定位置的位运算的应用
- #### 实战运算要点
