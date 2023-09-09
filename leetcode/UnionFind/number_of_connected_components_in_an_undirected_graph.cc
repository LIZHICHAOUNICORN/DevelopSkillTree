#include <algorithm>
#include <set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class UnionFind {
 public:
  UnionFind(int max_size) : parent_(max_size), rank_(max_size, 0) {
    iota(parent_.begin(), parent_.end(), 0);
  }
  void Union(int e1, int e2) {
    int root1 = Find(e1);
    int root2 = Find(e2);
    if (rank_[root1] > rank_[root2]) {
      swap(root1, root2);
    }
    parent_[root1] = root2;
    if (rank_[root1] == rank_[root2]) rank_[root1]--;
  }
  int Find(int e) {
    return parent_[e] == e ? e : parent_[e] = Find(parent_[e]);
  }

 private:
  vector<int> parent_;
  vector<int> rank_;
};

class Solution {
 public:
  int countComponents(int n, vector<vector<int>>& edges) {
    UnionFind uf(n);
    for (auto& edge : edges) {
      uf.Union(edge.front(), edge.back());
    }
    set<int> roots;
    for (int i = 0; i < n; ++i) {
      roots.insert(uf.Find(i));
    }
    return roots.size();
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> row1({0,1});
  vector<int> row2({1,2});
  vector<int> row3({3,4});
  vector<vector<int>> grid;
  grid.push_back(row1);
  grid.push_back(row2);
  grid.push_back(row3);

  int ret = solu.countComponents(5, grid);
  LOG(INFO) << ret;
  return 0;
}
