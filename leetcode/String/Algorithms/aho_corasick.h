#ifndef STRING_ALGORITHMS_AHO_CORSICK_
#define STRING_ALGORITHMS_AHO_CORSICK_

#include <queue>
#include <string>
#include <utility>
#include <vector>

// from: https://www.bilibili.com/video/BV1uJ411Y7Eg?p=1
// https://leetcode-cn.com/problems/multi-search-lcci/solution/kmpsuan-fa-zi-dian-shu-aczi-dong-ji-by-j-kir5/

namespace base {
using std::vector;
using std::string;
using std::queue;
using std::pair;

class AhoCorsick {
 private:
  static const int N = 1000 + 10;

  struct TrieNode {
    int fail;
  };

  int nodes_cnt_;
  vector<vector<int>> childs_;
  vector<int> values_;
  vector<int> f;

 public:
  AhoCorsick();
  ~AhoCorsick() = default;
  vector<pair<int, int>> multiSearch(const string& big, vector<string>& smalls);

  void Query(const string& word, vector<pair<int, int>>& ret);
  void Insert(const string& s);
  void BuildFail();
};

}  // namespace base
#endif
