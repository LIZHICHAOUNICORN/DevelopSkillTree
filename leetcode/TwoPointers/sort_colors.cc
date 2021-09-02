#include <vector>
#include <iostream>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using std::vector;

// Problem: https://leetcode-cn.com/problems/sort-colors/

// 单指针，两次遍历
class Solution {
 public:
  void sortColors(vector<int>& nums) {
      int n = nums.size();
      int ptr = 0;
      for (int i = 0; i < n; ++i) {
          if (nums[i] == 0) {
              std::swap(nums[i], nums[ptr]);
              ++ptr;
          }
      }
      for (int i = ptr; i < n; ++i) {
          if (nums[i] == 1) {
              std::swap(nums[i], nums[ptr]);
              ++ptr;
          }
      }
  }
};

void print_vector(vector<int> & nums) {
  return;
  for (int i = 0; i < nums.size(); ++i) {
    std::cout << nums[i] << "\t";
  }
  std::cout << std::endl;
}

class Solution1 {
 public:
  void sortColors(vector<int>& nums) {
    int n = nums.size();
    int p0 = 0, p1 = 0;
    for (int i = 0; i < n; ++i) {
      print_vector(nums);
      if (nums[i] == 1) {
          std::swap(nums[i], nums[p1]);
          ++p1;
          print_vector(nums);
      } else if (nums[i] == 0) {
          std::swap(nums[i], nums[p0]);
          print_vector(nums);
          if (p0 < p1) {
              std::swap(nums[i], nums[p1]);
              print_vector(nums);
          }
          ++p0;
          ++p1;
      }
    }
  }
};

class Solution2 {
 public:
  void sortColors(vector<int>& nums) {
      int n = nums.size();
      int p0 = 0, p2 = n - 1;
      for (int i = 0; i <= p2; ++i) {
          while (i <= p2 && nums[i] == 2) {
              std::swap(nums[i], nums[p2]);
              --p2;
          }
          if (nums[i] == 0) {
              std::swap(nums[i], nums[p0]);
              ++p0;
          }
      }
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution1 solu;
  vector<int> nums({2,0,2,1,1,0});
  solu.sortColors(nums);
  return 0;
}
