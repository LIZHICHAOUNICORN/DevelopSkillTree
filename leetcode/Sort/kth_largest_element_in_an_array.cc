#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/kth-largest-element-in-an-array

// quick sort
class Solution {
 public:
  int quickSelect(vector<int>& a, int l, int r, int index) {
    int q = randomPartition(a, l, r);
    if (q == index) {
      return a[q];
    } else {
      return q < index ? quickSelect(a, q + 1, r, index)
                       : quickSelect(a, l, q - 1, index);
    }
  }

  inline int randomPartition(vector<int>& a, int l, int r) {
    int i = rand() % (r - l + 1) + l;
    swap(a[i], a[r]);
    return partition(a, l, r);
  }

  inline int partition(vector<int>& a, int l, int r) {
    int x = a[r], i = l - 1;
    for (int j = l; j < r; ++j) {
      if (a[j] <= x) {
        swap(a[++i], a[j]);
      }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
  }

  int findKthLargest(vector<int>& nums, int k) {
    srand(time(0));
    return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
  }
};

class Solution1 {
 public:
  int partition(vector<int>& nums, int l, int r) {
    int temp = nums[l];
    while (l < r) {
      int temp = nums[l];
      while (l < r) {
        while (l < r && nums[r] <= temp) r--;
        swap(nums[l], nums[r]);
        while (l < r && nums[l] >= temp) l++;
        swap(nums[l], nums[r]);
      }
    }
    nums[l] = temp;
    return l;
  }
  int search(vector<int>& nums, int l, int r, int k) {
    int m = partition(nums, l, r);
    if (m == k - 1)
      return nums[m];
    else if (m > k - 1)
      return search(nums, l, m - 1, k);
    else
      return search(nums, m + 1, r, k);
  }
  int findKthLargest(vector<int>& nums, int k) {
    int length = nums.size();
    if (k > length)
      return 0;
    else
      return search(nums, 0, length - 1, k);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> nums({5, 1, 1, 2, 0, 0});
  Solution solu;
  int ret = solu.findKthLargest(nums, 4);
  LOG(INFO) << ret;

  return 0;
}
