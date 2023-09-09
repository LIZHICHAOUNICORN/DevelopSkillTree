#include "leetcode/String/Algorithms/aho_corasick.h"

#include <climits>
#include <cstring>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// from: https://www.bilibili.com/video/BV1uJ411Y7Eg?p=1
// https://leetcode-cn.com/problems/multi-search-lcci/solution/kmpsuan-fa-zi-dian-shu-aczi-dong-ji-by-j-kir5/

namespace base {
using std::vector;
using std::string;
using std::queue;
using std::pair;
using std::make_pair;

AhoCorsick::AhoCorsick()
    : childs_(N, vector<int>(26, 0)), values_(N, -1), nodes_cnt_(0), f(N, 0) {}

vector<std::pair<int, int>> AhoCorsick::multiSearch(const string& big,
                                                    vector<string>& smalls) {
  vector<pair<int, int>> ans;
  nodes_cnt_ = 0;

  for (int i = 0; i < smalls.size(); ++i) {
    if (smalls[i].empty()) {
      continue;
    }
    Insert(smalls[i]);
  }

  BuildFail();
  Query(big, ans);
  return ans;
}

void AhoCorsick::Query(const string& word, vector<pair<int, int>>& ans) {
  const string& big = word;
  // AC自动机匹配
  int j = 0;
  for (int i = 0; i < big.size(); ++i) {
    int c = big[i] - 'a';
    //沿着失配函数链，找到一个节点jf也有由c产生的子节点
    while (j && !childs_[j][c]) {
      j = f[j];
    }
    // j指向节点j由c产生的子节点
    j = childs_[j][c];
    int k = j;
    do {
      if (values_[k] >= 0) {
        int len = values_[k];
        ans.emplace_back(make_pair(i - len + 1, len));
      }
      k = f[k];
    } while (k);
  }
}

void AhoCorsick::Insert(const string& s) {
  int len = s.size();
  int r = 0;
  for (int i = 0; i < s.size(); ++i) {
    int idx = s[i] - 'a';

    int& next = childs_[r][idx];

    if (next == 0) {
      next = ++nodes_cnt_;
    }
    r = next;
  }
  values_[r] = len;
}

void AhoCorsick::BuildFail() {
  queue<int> Q;
  f[0] = 0;
  //根节点0的子节点j的失配函数f[j] = 0
  for (int c = 0; c < 26; ++c) {
    int j = childs_[0][c];
    if (j) {
      f[j] = 0;
      Q.push(j);
    }
  }
  while (Q.size()) {
    int j = Q.front();
    Q.pop();

    //计算节点j的子节点k的失配函数f[k]
    for (int c = 0; c < 26; ++c) {
      int k = childs_[j][c];
      if (!k) {
        continue;
      }
      // 从节点0到jf之前与从节点0到f[j]之前的部分有相同的后缀序列
      int jf = f[j];
      //沿着失配函数链，找到一个节点jf也有由c产生的子节点
      while (jf && !childs_[jf][c]) {
        jf = f[jf];
      }
      f[k] = childs_[jf][c];
      Q.push(k);
    }
  }
}

}  // namespace base
