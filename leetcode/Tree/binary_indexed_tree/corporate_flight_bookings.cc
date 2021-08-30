#include <vector>
#include <cstdlib>
#include <random>

#include "leetcode/Tree/tree_node.h"
#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/corporate-flight-bookings/
// Solutions: https://leetcode-cn.com/problems/corporate-flight-bookings/solution/hang-ban-yu-ding-tong-ji-by-leetcode-sol-5pv8/
// Solutions: https://leetcode-cn.com/problems/corporate-flight-bookings/solution/gong-shui-san-xie-yi-ti-shuang-jie-chai-fm1ef/

// 暴力解法
class Solution {
 public:
  vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> ret(n, 0);
    for (int k = 0; k < bookings.size(); ++k) {
      int start = bookings[k][0];
      int end = bookings[k][1];
      int seat = bookings[k][2];
      for (;start <= end; ++start) {
        ret[start-1] += seat;
      }
    }
    return ret;
  }
};

// 差分数组
class Solution {
 public:
  vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
      vector<int> nums(n);
      for (auto& booking : bookings) {
          nums[booking[0] - 1] += booking[2];
          if (booking[1] < n) {
              nums[booking[1]] -= booking[2];
          }
      }
      for (int i = 1; i < n; i++) {
          nums[i] += nums[i - 1];
      }
      return nums;
  }
};

// 线段树
class Solution {
 private:
  int tree[20005 << 2];
  void init() {
      memset(tree, 0, sizeof(tree));
  }
  void push_down(int k) {
      tree[k * 2] += tree[k];
      tree[k * 2 + 1] += tree[k];
      tree[k] = 0;
  }
  void update(int ql, int qr, int x, int l, int r, int k) {
      //cout << l << " " << r << endl;
      if (qr < l || ql > r) return; //无交集
      else if (ql <= l && r <= qr) tree[k] += x; //包含
      else {
          push_down(k); //下推操作，将先前的计算结果往子节点送
          int mid = (l + r) / 2; //左右子树分割点
          if (ql <= mid) update(ql, qr, x, l, mid, k * 2); //左子树
          if (qr > mid) update(ql, qr, x, mid + 1, r, k * 2 + 1); //右子树
      }
  }
  int query(int ql, int qr, int l, int r, int k) {
      if (qr < l || ql > r) return -1; //无交集
      else if (ql <= l && r <= qr) return tree[k]; //包含
      else {
          push_down(k); //下推操作，将先前的计算结果往子节点送
          int mid = (l + r) / 2; //左右子树分割点
          if (ql <= mid) return query(ql, qr, l, mid, k * 2); //左子树
          if (qr > mid) return query(ql, qr, mid + 1, r, k * 2 + 1); //右子树
      }
      return -1;
  }
 public:
  vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
      init();
      for (const auto& it : bookings) {
          update(it[0], it[1], it[2], 1, n, 1);
      }
      vector<int> res;
      for (int i = 1; i <= n; ++i) {
          res.push_back(query(i, i, 1, n, 1));
      }
      return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  return 0;
}
