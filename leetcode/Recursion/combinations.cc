#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// backtrack
class Solution {
 private:
  vector<vector<int>> res;
  //前start-1个组合已经完成
  // 求解C(n,k), 当前已经找到的组合存储在c中, 需要从start开始搜索新的元素
  void generateCombinations(int n, int k, int start, vector<int>& c) {
    if (c.size() == k) {
      res.push_back(c);
      return;
    }

    for (int i = start; i <= n; i++) {
      c.push_back(i);
      generateCombinations(n, k, i + 1, c);

      // 回溯
      c.pop_back();
    }
    return;
  }

 public:
  vector<vector<int>> combine(int n, int k) {
    res.clear();

    if (n <= 0 || k <= 0) {
      return res;
    }
    vector<int> c;
    generateCombinations(n, k, 1, c);
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> input = {1, 2};
  vector<vector<int>> ret = solu.combine(2, 4);
  return 0;
}
