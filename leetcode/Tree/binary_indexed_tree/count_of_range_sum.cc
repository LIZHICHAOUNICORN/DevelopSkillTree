#include <vector>
#include <iostream>

using namespace std;

// exceeded time.
// Binary indexed tree.
class Solution {
private:
    vector<long long> tree;
    int lowbit(int x) {
        return x & -x;
    }
    void add(int pos, int diff) {
        for (int i = pos; i < tree.size(); i += lowbit(i)) {
            tree[i] += diff;
        }
    }
    long long query(int pos) {
        long long ans = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            ans += tree[i];
        }
        return ans;
    }
    bool CheckValid(long long target, long long low, long long up) {
        if (target >= low && target <= up) return true;
        return false;
    }

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        // build tree
        tree.assign(nums.size()+1, 0);
        for (int i = 0; i < nums.size(); ++i) {
            add(i+1, nums[i]);
        }
        int result = 0;
        for (int i = 0; i <= nums.size(); ++i) {
            for (int j = i+1; j <= nums.size(); ++j) {
                long long ans = query(j) - query(i);
                CheckValid(ans, lower, upper) ? result += 1 : result ;
            }
        }
        return result;
    }
};


int main(int argc, char* argv[]) {
    //   google::InitGoogleLogging(argv[0]);
    //   gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> nums = {1,3,5};

  Solution solu;
  int ret = solu.countRangeSum(nums, 0, 2);
  std::cout << ret << std::endl;

  return 0;
}
