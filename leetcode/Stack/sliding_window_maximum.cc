#include <vector>
#include <limits>
#include <algorithm>
#include <stack>
#include <deque>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;


// comments:
// https://leetcode-cn.com/problems/sliding-window-maximum/solution/dan-diao-dui-lie-by-labuladong/ NOLINT

class MonotonicQueue {
 private:
   deque<int> data;
 public:
   void push(int n) {
     while (!data.empty() && data.back() < n) {
       data.pop_back();
     }
     data.push_back(n);
   }
   int max() { return data.front(); }
   void pop(int n) {
     if (!data.empty() && data.front() == n) {
       data.pop_front();
     }
   }
};

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    MonotonicQueue window;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
      if (i < k - 1) { //先填满窗口的前 k - 1
        window.push(nums[i]);
      } else { // 窗口向前滑动
        window.push(nums[i]);
        res.push_back(window.max());
        window.pop(nums[i - k + 1]);
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  int array_value[] = {1,3,-1,-3,5,3,6,7};
  int k = 3;
  vector<int> input_value(array_value, array_value + sizeof(array_value)/sizeof(int));
  Solution solu;
  solu.maxSlidingWindow(input_value, k);
  for (size_t i = 0; i < input_value.size(); ++i) {
    DLOG(INFO) << input_value[i];
  }
  return 0;
}
