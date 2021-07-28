#include <vector>
#include <iostream>

using namespace std;


class NumArray {
 private:
    vector<int> tree;
    vector<int>& nums;

    int lowbit(int x) {
      return x & -x;
    }
    
    int query(int x) {
      int ans = 0;
      for(int i = x; i > 0; i -= lowbit(i)) {
        ans += tree[i];
      }
      return ans;
    }

    void add(int x, int u) {
      for(int i = x; i <= nums.size(); i += lowbit(i)) {
        tree[i] += u;
      }
    }
 public:
    NumArray(vector<int>& nums) :
        nums(nums),
        tree(nums.size()+1, 0) {
      for(int i = 0; i < nums.size(); i++) {
        add(i+1, nums[i]);
      }
    }
    
    void update(int index, int val) {
      add(index+1, val-nums[index]);
      nums[index] = val;
    }

    int sumRange(int left, int right) {
      return query(right+1) - query(left);
    }
};


int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> nums = {1,3,5};

  NumArray num_arr(nums);
  int ret = num_arr.sumRange(0, 2);
  std::cout << ret << std::endl;
  num_arr.update(1, 2);
  ret = num_arr.sumRange(0, 2);
  std::cout << ret << std::endl;

  return 0;
}
