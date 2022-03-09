#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int Partition(vector<int>& nums, int l, int r) {
    int pivot = nums[r];
    int i = l;
    int j = l;
    for (; j < r; ++j) {
      if (nums[j] < pivot) {
        swap(nums[i], nums[j]);
        ++i;
      }
    }
    nums[r] = nums[i];
    nums[i] = pivot;
    return i;
  }
  void QuickSort(vector<int>& nums, int l, int r) {
    if (l < r) {
      int mid = Partition(nums, l, r);
      QuickSort(nums, l, mid - 1);
      QuickSort(nums, mid + 1, r);
    }
  }
};

int main(int argc, char* argv[]) {
  vector<int> nums({1, 3, 2, 2, 4, 6});

  Solution solu;
  solu.QuickSort(nums, 0, nums.size() - 1);

  return 0;
}
