#include <algorithm>
#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/max-points-on-a-line/

using namespace std;

class Solution {
 public:
  int maxPoints(vector<vector<int>>& points) {
    int len = points.size();
    // 点的数量不够
    if (len < 3) {
      return len;
    }
    int maxNum = 2;
    // 遍历每两个点
    for (int i = 0; i < len - 1; i++) {
      for (int j = i + 1; j < len; j++) {
        // 统计斜率相等个数
        int count = 2;
        long long dx = points[i][0] - points[j][0];
        long long dy = points[i][1] - points[j][1];
        // 与其他点比较
        for (int k = j + 1; k < len; k++) {
          // 如果斜率相等
          if (dx * (points[i][1] - points[k][1]) ==
              dy * (points[i][0] - points[k][0])) {
            count++;
          }
        }
        maxNum = max(maxNum, count);
        if (maxNum > len / 2) return maxNum;
      }
    }
    return maxNum;
  }
};

class Solution1 {
 public:
  int maxPoints(vector<vector<int>>& points) {
    int len = points.size();
    // 点的数量不够
    if (len < 3) {
      return len;
    }
    int maxNum = 2;
    // 遍历每两个点
    for (int i = 0; i < len; i++) {
      unordered_map<double, int> count;
      for (int j = 0; j < len; j++) {
        if (i != j) {
          long long dx = points[i][0] - points[j][0];
          long long dy = points[i][1] - points[j][1];
          double gradient = dy * 1.0 / dx;
          if (count.count(gradient)) {
            count[gradient]++;
          } else {
            count[gradient] = 2;
          }
          maxNum = max(maxNum, count[gradient]);
        }
      }
    }
    return maxNum;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<int>> words({{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}});

  Solution solu;
  auto ret = solu.maxPoints(words);
  LOG(INFO) << ret;
  return 0;
}
