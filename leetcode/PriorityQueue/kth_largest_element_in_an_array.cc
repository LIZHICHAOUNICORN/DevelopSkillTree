#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
class Solution {
 public:
  void maxHeapify(vector<int>& a, int i, int heapSize) {
    int l = i * 2 + 1, r = i * 2 + 2, largest = i;
    if (l < heapSize && a[l] > a[largest]) {
      largest = l;
    }
    if (r < heapSize && a[r] > a[largest]) {
      largest = r;
    }
    if (largest != i) {
      swap(a[i], a[largest]);
      maxHeapify(a, largest, heapSize);
    }
  }

  void buildMaxHeap(vector<int>& a, int heapSize) {
    for (int i = heapSize / 2; i >= 0; --i) {
      maxHeapify(a, i, heapSize);
    }
  }

  int findKthLargest(vector<int>& nums, int k) {
    int heapSize = nums.size();
    buildMaxHeap(nums, heapSize);
    for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
      swap(nums[0], nums[i]);
      --heapSize;
      maxHeapify(nums, 0, heapSize);
    }
    return nums[0];
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
