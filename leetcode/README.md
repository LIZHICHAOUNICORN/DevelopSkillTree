# Algorithms and Data Structures

## TODO List
- [ ] Basic Operation
  - [x] Array
  - [x] String
  - [ ] Sort
  - [ ] Bucket-sort
  - [ ] Counting-sort
  - [ ] Radix-sort
  - [x] Matrix
  - [x] Simulation
  - [ ] Enumeration
  - [ ] String-matching
- [ ] Algorithms
  - [x] Dynamic-programming
  - [x] Depth-first-search
  - [x] Breadth-first-search
  - [x] greedy
  - [x] binary-search
  - [x] backtracking
  - [x] recursion
  - [ ] divide-and-conquer
  - [x] memoization
  - [ ] quickselect
  - [ ] merge-sort
- [ ] Basic Data Structures
  - [ ] hash-table
  - [x] tree
  - [x] binary-tree
  - [x] stack
  - [x] heap-priority-queue
  - [ ] graph
  - [x] linked-list
  - [x] binary-search-tree
  - [ ] monotonic-stack
  - [x] queue
  - [ ] ordered-set
  - [ ] topological-sort
  - [ ] shortest-path
  - [ ] doubly-linked-list
  - [ ] monotonic-queue
  - [ ] minimum-spanning-tree
  - [ ] strongly-connected-component
  - [ ] eulerian-circuit
  - [ ] biconnected-component
- [ ] Advance Data Structures
  - [ ] union-find
  - [x] trie
  - [ ] segment-tree
  - [ ] binary-indexed-tree
  - [ ] suffix-array
- [ ] Trick
  - [x] two-pointers
  - [ ] bit-manipulation
  - [ ] sliding-window
  - [x] prefix-sum
  - [ ] counting
- [ ] Math
  - [x] math
  - [ ] geometry
  - [ ] game-theory
  - [ ] randomized
  - [ ] combinatorics
- [ ] Other
  - [x] design


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

## LRU Cache

- #### Hash table 以及对比


- #### 概要
1. 两个要素： 大小，替换策略；
2. 实现方式： Hash table + Double LinkedList，从LeetCode实现中推荐一下两个，备份见文件
	2.1 [leetcode1](https://leetcode-cn.com/problems/lru-cache/solution/lru-ce-lue-xiang-jie-he-shi-xian-by-labuladong/)
	[leetcode2](https://leetcode-cn.com/problems/lru-cache/solution/shu-ju-jie-gou-fen-xi-python-ha-xi-shuang-xiang-li/)

		class LRUCache {
		  private:
    		int cap;
    		// 双链表：装着 (key, value) 元组
    		list<pair<int, int>> cache;
    		// 哈希表：key 映射到 (key, value) 在 cache 中的位置
    		unordered_map<int, list<pair<int, int>>::iterator> map;
		  public:
    		    LRUCache(int capacity) {
        	      this->cap = capacity; 
    	            }
    
    		int get(int key) {
        		auto it = map.find(key);
        		// 访问的 key 不存在
        		if (it == map.end()) return -1;
        		// key 存在，把 (k, v) 换到队头
        		pair<int, int> kv = *map[key];
        		cache.erase(map[key]);
        		cache.push_front(kv);
        		// 更新 (key, value) 在 cache 中的位置
        		map[key] = cache.begin();
        		return kv.second; // value
    		}
		
    		void put(int key, int value) {

        	/* 要先判断 key 是否已经存在 */ 
        	auto it = map.find(key);
        	if (it == map.end()) {
            		/* key 不存在，判断 cache 是否已满 */ 
            		if (cache.size() == cap) {
                	// cache 已满，删除尾部的键值对腾位置
                	// cache 和 map 中的数据都要删除
                	auto lastPair = cache.back();
                	int lastKey = lastPair.first;
                	map.erase(lastKey);
               		cache.pop_back();
            	}
            		// cache 没满，可以直接添加
            		cache.push_front(make_pair(key, value));
            		map[key] = cache.begin();
        	} else {
        	    	/* key 存在，更改 value 并换到队头 */
            		cache.erase(map[key]);
            		cache.push_front(make_pair(key, value));
           	 	map[key] = cache.begin();
        	}
    	      }
	    };



 	2.2. 实现要点：
 		（1）必须是双向链表，单链表不行。因为我们需要删除操作。删除一个节点不光要得到该节点本身的指针，也需要操作其前驱节点的指针，而双向链表才能支持直接查找前驱，保证操作的时间复杂度。
 		（2）哈希表中已经存了key，同时链表中也必须存储key，当缓存容量已满，我们不仅仅要删除最后一个 Node 节点，还要把 map 中映射到该节点的 key 同时删除，而这个 key 只能由 Node 得到。如果 Node 结构中只存储 val，那么我们就无法得知 key 是什么，就无法删除 map 中的键，造成错误。
3. 操作复杂度： O(1) 查询， O(1) 修改，更新
- #### 工作示例
示意图如下：
![](https://github.com/LIZHICHAOUNICORN/arsenal/blob/master/leetcode/src/lru%E5%AE%9E%E7%8E%B0%E7%A4%BA%E6%84%8F%E5%9B%BE.jpeg?raw=true)

- #### 替换策略
替换策略详见文件 src/Cache replacement policies - Wikipedia.pdf.
较为常用的是 [Least recently used (LRU)](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)) 和 [Least-frequently used (LFU)](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least-frequently_used_(LFU))

- #### TODO
补充其他替换策略的 cache以及 分析cache-server实现

## Bloom Filter

- #### Bloom filter
1. 一个很长的二进制向量和一系列随机映射函数。Bloom filter可以用于检测一个元素是否在一个集合中。
2. 优点：空间效率和时间效率远传一般算法。
3. 缺点：有一定误识别率和删除空难。
- #### 实现原理
例如：对于一个代表url的 x , 经过一个随机映射函数，得到映射这个url后的二进制向量01...1..1，将对应的二进制向量中对应位置设置为1，当新过来一个变量，检查它是否在这个集合中，那么就检查它映射后二进制向量是否为为1。  示意图如下：

![](https://github.com/LIZHICHAOUNICORN/arsenal/blob/master/leetcode/src/bloomfilter%20%E5%8E%9F%E7%90%86%E7%A4%BA%E6%84%8F%E5%9B%BE.png?raw=true)

通过上述分析，可能已经知道，Bloom filter错误来自于 映射后的二进制向量是否已经被都设置为1，如果凑巧都设置为1，那么就可能发生误认为存在于集合中，示意图如下：

![](https://github.com/LIZHICHAOUNICORN/arsenal/blob/master/leetcode/src/bloomfilter%20%E9%94%99%E8%AF%AF%E7%A4%BA%E6%84%8F%E5%9B%BE.png?raw=true)

- #### 应用
1. 比特币网络
2. 分布式系统(map-reduce) - Hadoop, search engine
3. Redis缓存
4. 垃圾邮件、评论等过滤

- #### TODO
错误率的量化以及bloom filter的实现

