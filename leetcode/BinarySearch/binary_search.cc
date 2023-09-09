#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::vector;
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int mid = 0;
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
      mid = (l + r) / 2;
      if (nums[mid] == target) break;
      if (nums[mid] > target) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    if (nums[mid] != target) return -1;
    return mid;
  }
};

// 版本二
class Solution1 {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size();  // 定义target在左闭右开的区间里，即：[left, right)
    while (left < right) {  // 因为left == right的时候，在[left,
                            // right)是无效的空间，所以使用 <
      int middle = left + ((right - left) >> 1);
      if (nums[middle] > target) {
        right = middle;  // target 在左区间，在[left, middle)中
      } else if (nums[middle] < target) {
        left = middle + 1;  // target 在右区间，在[middle + 1, right)中
      } else {              // nums[middle] == target
        return middle;      // 数组中找到目标值，直接返回下标
      }
    }
    // 未找到目标值
    return -1;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> nums({5, 7, 8, 10});
  solu.search(nums, 8);
  return 0;
}
