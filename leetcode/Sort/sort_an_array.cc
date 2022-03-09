#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/sort-an-array

// quick sort
class Solution {
 public:
  vector<int> sortArray(vector<int>& nums) {
    QuickSort(nums, 0, nums.size() - 1);
    return nums;
  }
  void QuickSort(vector<int>& nums, int l, int r) {
    if (l < r) {
      int mid = partition(nums, l, r);
      QuickSort(nums, l, mid - 1);  //注意点，l和r的值自己写错
      QuickSort(nums, mid + 1, r);  //注意点,l和r的值自己写错
    }
  }

  int partition(vector<int>& nums, int l, int r) {
    //选取不同的主元，交换方式不一样，选取左主元，得从右向左遍历，且判断该pivot是否小于当前元素，小于则交换
    //下面以右主元为例
    int pivot = nums[r];
    //两个指针,一者移动
    int i = l, j = l;
    //遍历序列，找主元应该插入的位置
    for (; j < r; j++) {
      //交换
      if (nums[j] < pivot) {
        swap(nums[j], nums[i]);
        i++;
      }
    }
    nums[r] = nums[i];
    nums[i] = pivot;
    return i;  //返回分割位置
  }
};

// Heap sort
class Solution2 {
  void maxHeapify(vector<int>& nums, int i, int len) {
    for (; (i << 1) + 1 <= len;) {
      int lson = (i << 1) + 1;
      int rson = (i << 1) + 2;
      int large;
      if (lson <= len && nums[lson] > nums[i]) {
        large = lson;
      } else {
        large = i;
      }
      if (rson <= len && nums[rson] > nums[large]) {
        large = rson;
      }
      if (large != i) {
        swap(nums[i], nums[large]);
        i = large;
      } else {
        break;
      }
    }
  }
  void buildMaxHeap(vector<int>& nums, int len) {
    for (int i = len / 2; i >= 0; --i) {
      maxHeapify(nums, i, len);
    }
  }
  void heapSort(vector<int>& nums) {
    int len = (int)nums.size() - 1;
    buildMaxHeap(nums, len);
    for (int i = len; i >= 1; --i) {
      swap(nums[i], nums[0]);
      len -= 1;
      maxHeapify(nums, 0, len);
    }
  }

 public:
  vector<int> sortArray(vector<int>& nums) {
    heapSort(nums);
    return nums;
  }
};

// Merge sort
class Solution1 {
  vector<int> tmp;
  void mergeSort(vector<int>& nums, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid + 1, r);
    int i = l, j = mid + 1;
    int cnt = 0;
    while (i <= mid && j <= r) {
      if (nums[i] <= nums[j]) {
        tmp[cnt++] = nums[i++];
      } else {
        tmp[cnt++] = nums[j++];
      }
    }
    while (i <= mid) {
      tmp[cnt++] = nums[i++];
    }
    while (j <= r) {
      tmp[cnt++] = nums[j++];
    }
    for (int i = 0; i < r - l + 1; ++i) {
      nums[i + l] = tmp[i];
    }
  }

 public:
  vector<int> sortArray(vector<int>& nums) {
    tmp.resize((int)nums.size(), 0);
    mergeSort(nums, 0, (int)nums.size() - 1);
    return nums;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> nums({5, 1, 1, 2, 0, 0});
  Solution solu;
  vector<int> ret = solu.sortArray(nums);
  for (const int& r : ret) {
    LOG(INFO) << r;
  }

  return 0;
}
