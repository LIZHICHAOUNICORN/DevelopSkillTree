#include <numeric>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<int> findErrorNums(vector<int>& nums) {
    sort(begin(nums), end(nums));
    // twice value
    auto d = adjacent_find(begin(nums), end(nums));
    // s:  sum of nums
    auto s = accumulate(begin(nums), end(nums), 0);
    vector<int> ret;
    ret.push_back(*d);
    // missing value: sum n*(n+1)/2 - s + *d
    ret.push_back(nums.size() *(nums.size()+1)/2-s+*d);
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
