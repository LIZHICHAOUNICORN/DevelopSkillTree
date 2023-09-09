#include <algorithm>
#include <vector>
#include <numeric>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// version 1
class UnionFindV1 {
 private:
  std::vector<int> parent;

 public:
  UnionFindV1(int max_size) : parent(std::vector<int>(max_size)) {
    // 初始化每一个元素的根节点都为自身
    std::iota(parent.begin(), parent.end(), 0);
  }

  int Find(int x) { return parent[x] == x ? x : Find(parent[x]); }
  void Union(int x1, int x2) { parent[Find(x1)] = Find(x2); }
  // 判断两个元素是否属于同一个集合
  bool IsSame(int e1, int e2) { return Find(e1) == Find(e2); }
};

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
    std::iota(parent.begin(), parent.end(), 0);
  }
  int Find(int x) { return x == parent[x] ? x : (parent[x] = Find(parent[x])); }
  void Union(int x1, int x2) {
    int root1 = Find(x1);
    int root2 = Find(x2);
    if (rank[root1] > rank[root2])
      parent[root2] = root1;
    else {
      parent[root1] = root2;
      if (rank[root1] == rank[root2]) ++rank[root2];
    }
  }
  bool IsSame(int e1, int e2) { return Find(e1) == Find(e2); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  UnionFind uf(10);
  LOG(INFO) << uf.IsSame(1, 2);

  uf.Union(1, 2);
  LOG(INFO) << uf.IsSame(1, 2);

  uf.Union(2, 3);
  LOG(INFO) << uf.IsSame(1, 3);

  return 0;
}
