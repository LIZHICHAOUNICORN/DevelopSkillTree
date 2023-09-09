#include <climits>
#include <stack>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problems: https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
// Solutions:
// https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/zhu-zhuang-tu-zhong-zui-da-de-ju-xing-by-leetcode-/

// 暴力解法，两次遍历宽
class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    int ans = 0;
    // 枚举左边界
    for (int left = 0; left < n; ++left) {
      int minHeight = INT_MAX;
      // 枚举右边界
      for (int right = left; right < n; ++right) {
        // 确定高度
        minHeight = min(minHeight, heights[right]);
        // 计算面积
        ans = max(ans, (right - left + 1) * minHeight);
      }
    }
    return ans;
  }
};

// 暴力解法，两次遍历高
class Solution2 {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    int ans = 0;
    for (int mid = 0; mid < n; ++mid) {
      // 枚举高
      int height = heights[mid];
      int left = mid, right = mid;
      // 确定左右边界
      while (left - 1 >= 0 && heights[left - 1] >= height) {
        --left;
      }
      while (right + 1 < n && heights[right + 1] >= height) {
        ++right;
      }
      // 计算面积
      ans = max(ans, (right - left + 1) * height);
    }
    return ans;
  }
};

// 单调栈优化， O(n)
class Solution1 {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n), right(n);

    stack<int> mono_stack;
    for (int i = 0; i < n; ++i) {
      while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
        mono_stack.pop();
      }
      left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
      mono_stack.push(i);
    }

    mono_stack = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
      while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
        mono_stack.pop();
      }
      right[i] = (mono_stack.empty() ? n : mono_stack.top());
      mono_stack.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> temperatures({2, 1, 5, 6, 2, 3});

  Solution solu;
  int ret = solu.largestRectangleArea(temperatures);
  LOG(INFO) << ret;

  return 0;
}
