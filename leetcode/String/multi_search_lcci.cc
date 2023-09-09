#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;
// Problem: https://leetcode-cn.com/problems/multi-search-lcci/

const int N = 100000 + 10;
int childs[N][26];
int values[N];
int nodes_cnt;
int f[N];
class Solution {
 public:
  vector<vector<int>> multiSearch(string big, vector<string>& smalls) {
    vector<vector<int>> ans(smalls.size());
    memset(childs, 0, sizeof(childs));
    memset(values, 0xff, sizeof(values));
    nodes_cnt = 0;
    memset(f, 0, sizeof(f));

    //构造字典树，原理见算法二
    for (int i = 0; i < smalls.size(); ++i) {
      if (smalls[i].empty()) {
        continue;
      }
      insert(smalls[i], i);
    }

    getFail();

    // AC自动机匹配
    int j = 0;
    for (int i = 0; i < big.size(); ++i) {
      int c = big[i] - 'a';
      //沿着失配函数链，找到一个节点jf也有由c产生的子节点
      while (j && !childs[j][c]) {
        j = f[j];
      }
      // j指向节点j由c产生的子节点
      j = childs[j][c];
      int k = j;
      do {
        if (values[k] >= 0) {
          int len = smalls[values[k]].size();
          ans[values[k]].push_back(i - len + 1);
        }
        k = f[k];
      } while (k);
    }

    return ans;
  }

  void insert(const string& s, int index_of_s) {
    int r = 0;
    for (int i = 0; i < s.size(); ++i) {
      int idx = s[i] - 'a';

      int& next = childs[r][idx];
      // printf("%d %d %d %d\n",r,idx,next,nodes_cnt);
      if (next == 0) {
        next = ++nodes_cnt;
      }
      r = next;
    }
    values[r] = index_of_s;
  }

  void getFail() {
    queue<int> Q;
    f[0] = 0;
    //根节点0的子节点j的失配函数f[j] = 0
    for (int c = 0; c < 26; ++c) {
      int j = childs[0][c];
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
        int k = childs[j][c];
        if (!k) {
          continue;
        }
        int jf =
            f[j];  //从节点0到jf之前与从节点0到f[j]之前的部分有相同的后缀序列
        //沿着失配函数链，找到一个节点jf也有由c产生的子节点
        while (jf && !childs[jf][c]) {
          jf = f[jf];
        }
        f[k] = childs[jf][c];
        Q.push(k);
      }
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> smalls({"is", "ppi", "hi", "sis", "i", "ssippi"});

  Solution solu;
  auto ret = solu.multiSearch("mississippi", smalls);
  for (auto& vec : ret) {
    for (auto& it : vec) {
      std::cout << it << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
