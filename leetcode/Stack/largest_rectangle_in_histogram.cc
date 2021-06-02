#include <vector>
#include <limits>
#include <algorithm>
#include <stack>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

// version 1: bruce, over time
class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    if (heights.empty()) return 0;
    if (heights.size() == 1) return heights[0];
    int max_size = 0;
    for (int i = 0; i < heights.size(); ++i) {
      for (int j = heights.size() - 1; j >= 0; --j) {
        int start = min(i, j);
        int end = max(i, j);
        int len = end - start;
        int height = FindMin(heights, start, end + 1);
        len += 1;
        DLOG(INFO) << "start: " << start
                   << ",end: " << end
                   << ", height: " << height
                   << ", lenght: " << len;
        max_size = max(max_size, len * height);
      }
    }
    return max_size;
  }
 private:
  int FindMin(vector<int>& nums, size_t start, size_t end) {
    int min_val = nums[start];
    for (size_t i = start; i < nums.size() && i < end ; ++i) {
      if (min_val > nums[i]) min_val = nums[i];
    }
    return min_val;
  }
};

// version 2: overtime 
class Solution1 {
 public:
  int largestRectangleArea(vector<int>& heights) {
    if (heights.empty()) return 0;
    if (heights.size() == 1) return heights[0];
    int max_size = 0;
    for (int i = 0; i < heights.size(); ++i) {
      int height = heights[i];
      for (int j = i; j < heights.size(); ++j) {
        int len = j - i + 1;
        height = min(height, heights[j]);
        DLOG(INFO) << ", height: " << height
                   << ", lenght: " << len;
        max_size = max(max_size, len * height);
      }
    }
    return max_size;
  }
};

// version3:
class Solution2 {
 public:
  int largestRectangleArea(vector<int>& heights) {
    return 0;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  // int array_value[] = {4,2};
  // int array_value[] = {2,1,5,6,2,3};
  // int array_value[] = {9,0};
  // int array_value[] = {1,2,3,4,5};
  // vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  vector<int> input_value;
  for (int i = 0; i < 20000; ++i) {
    input_value.push_back(i);
  }
  Solution solu;
  int max_size = solu.largestRectangleArea(input_value);
  LOG(INFO) << "max size: " << max_size;
  return 0;
}
