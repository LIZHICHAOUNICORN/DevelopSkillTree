
## 应用场景

## 实现
```cpp
// version 1
class UnionFind {
 private:
  std::vector<int> parent;

 public:
  UnionFind(int max_size) : parent(std::vector<int>(max_size)) {
    // 初始化每一个元素的根节点都为自身
    iota(parent.begin(), parent.end(), 0);
  }
  int Find(int x) { return parent[x] == x ? x : Find(parent[x]); }
  void Union(int x1, int x2) { parent[Find(x1)] = Find(x2); }
  // 判断两个元素是否属于同一个集合
  bool IsSame(int e1, int e2) { return Find(e1) == Find(e2); }
};

// version 2
// 两点优化:
// 1) 增加秩（单元高度），即在union时，比较秩的大小，将秩小的合并到大的.
// 2) 路径压缩，执行Find的过程中，将路径上的所有节点都直接连接到根节点上。
// 时间复杂度：O(alpha(n))(在n非常大的时候，alpha(n)依然小于5), 空间复杂度O(n).
class UnionFind {
 private:
  std::vector<int> parent;
  std::vector<int> rank;  // 秩

 public:
  UnionFind(int max_size)
      : parent(std::vector<int>(max_size)),
        rank(std::vector<int>(max_size, 0)) {
    iota(parent.begin(), parent.end(), 0);
  }
  int Find(int x) { return x == parent[x] ? x : (parent[x] = Find(parent[x])); }
  void Union(int x1, int x2) {
    int f1 = Find(x1);
    int f2 = Find(x2);
    if (rank[f1] > rank[f2])
      parent[f2] = f1;
    else {
      parent[f1] = f2;
      if (rank[f1] == rank[f2]) ++rank[f2];
    }
  }
  bool IsSame(int e1, int e2) { return Find(e1) == Find(e2); }
};
```


## TODO List
- [X] [130. surrounded-regions](https://leetcode-cn.com/problems/surrounded-regions/)
- [X] [200. number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)
- [X] [friend-circles](https://leetcode-cn.com/problems/friend-circles/)
- [X] [684. redundant-connection](https://leetcode-cn.com/problems/redundant-connection/)
