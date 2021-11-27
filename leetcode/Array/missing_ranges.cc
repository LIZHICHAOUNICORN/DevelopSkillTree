#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/missing-ranges/

using namespace std;

class Solution {
 public:
  vector<string> ans;
  inline void add(int l, int r) {
    //真的需要添加区间 [l,r] 吗？
    //比如 [8,2] 显然不需要，而且像 (3,4) 区间也是不缺数的
    if (l + 1 >= r) return;

    if (l + 2 == r) {
      ans.push_back(to_string(l + 1));
    } else {
      ans.push_back(to_string(l + 1) + "->" + to_string(r - 1));
    }
  }
  vector<string> findMissingRanges(vector<int>& a, int L, int R) {
    int n = a.size();

    --L;
    ++R;           //变成开区间
    if (n == 0) {  //一个区间都不给的屑力扣。只好当成 {L,R}
      add(L, R);
      return ans;
    }
    // 我们有 { L, a[0], a[1], ..., a[n-1], R } 这些数
    add(L, a[0]);
    for (int i = 1; i < n; ++i) {
      add(a[i - 1], a[i]);
    }
    add(a[n - 1], R);
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> tasks({0, 1, 3, 50, 75});

  Solution solu;
  auto ret = solu.findMissingRanges(tasks, 0, 99);
  LOG(INFO) << ret.back();

  return 0;
}
