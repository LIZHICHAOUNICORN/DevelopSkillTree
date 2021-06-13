// Time: 2021年06月13日
// Author: Zhichao Li

#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>

using std::vector;

// base version
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        // Sum
        for (auto iter = nums.cbegin(); iter != nums.cend(); ++iter) {
            sum += *iter;
        }
        if (sum % 2 == 1) return false;
        vector<int> dp(10001, 0);

        int target = sum/2;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = target; j >= nums[i]; --j) {
                dp[j] = std::max(dp[j], dp[j-nums[i]] + nums[i]);
            }
        }
        if (dp[target] == target) return true;
        return false;
    }
};

// version 2
class Solution1 {
public:
    bool canPartition(vector<int>& nums) {

        if (nums.size() < 2) return false;

        int sum = std::accumulate(nums.begin(), nums.end(), 0);
//        for (auto iter = nums.cbegin(); iter != nums.cend(); ++iter) {
//            sum += *iter;
//        }

        if (0 != (1 & sum)) return false;
//      if (sum % 2 == 1) return false;

        int target = sum/2;
        int max = *(std::max_element(nums.begin(), nums.end()));
        if (max > target) return false;

        // Dont know why this operation.
//        std::bitset<((200 * 100) >> 1) + 1> alpha(1);
//        for (auto n : nums) {
//            alpha |= (alpha << n);
//        }
//        return 1 == alpha[sum >> 1];

        vector<int> dp(10001, 0);
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = target; j >= nums[i]; --j) {
                dp[j] = std::max(dp[j], dp[j-nums[i]] + nums[i]);
            }
        }
        if (dp[target] == target) return true;
        return false;
    }
};


int main(int argc, char* argv[]) {
    Solution solu;
    vector<int> nums({1,5,11,5});
    bool ret = solu.canPartition(nums);
    std::cout << "Result : " << ret << std::endl;
    return 0;

}

