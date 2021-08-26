#include <vector>
#include <queue>
#include <cstdlib>
#include <random>
#include <algorithm>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

DEFINE_int32(input_size, 10, "input data size");

using namespace std;

// Problem: https://leetcode-cn.com/problems/search-in-rotated-sorted-array
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = (int)nums.size();
        if (!n) {
            return -1;
        }
        if (n == 1) {
            return nums[0] == target ? 0 : -1;
        }
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == target) return mid;
            if (nums[0] <= nums[mid]) {
                if (nums[0] <= target && target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[n - 1]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  // Build test case.
  vector<vector<int>> flights;
  vector<int> flight1({1,2});
  vector<int> flight2({3});
  vector<int> flight3({3});
  vector<int> flight4({});
  flights.push_back(flight1);
  flights.push_back(flight2);
  flights.push_back(flight3);
  flights.push_back(flight4);

  Solution solu;
  auto paths = solu.allPathsSourceTarget(flights);
  return 0;
}
