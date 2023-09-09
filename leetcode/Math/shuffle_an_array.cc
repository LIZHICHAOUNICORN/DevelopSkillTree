#include <cmath>
#include <stack>
#include <list>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/shuffle-an-array/
// Solution
// https://leetcode-cn.com/problems/shuffle-an-array/solution/da-luan-shu-zu-by-leetcode-solution-og5u/

class Solution {
 public:
  Solution(vector<int>& nums) {
    this->nums = nums;
    this->original.resize(nums.size());
    copy(nums.begin(), nums.end(), original.begin());
  }

  vector<int> reset() {
    copy(original.begin(), original.end(), nums.begin());
    return nums;
  }

  vector<int> shuffle() {
    vector<int> shuffled = vector<int>(nums.size());
    list<int> lst(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); ++i) {
      int j = rand() % (lst.size());
      auto it = lst.begin();
      advance(it, j);
      shuffled[i] = *it;
      lst.erase(it);
    }
    copy(shuffled.begin(), shuffled.end(), nums.begin());
    return nums;
  }

 private:
  vector<int> nums;
  vector<int> original;
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<int> nums({1,2,3,4});

  Solution solu(nums);
  vector<int> ret = solu.shuffle();

  solu.reset();
  return 0;
}
