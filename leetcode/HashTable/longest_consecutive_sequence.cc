#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

using namespace std;
// Problem: https://leetcode-cn.com/problems/longest-consecutive-sequence/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }
        return longestStreak;           
    }
};



int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> anagram({"eat","tea","tan","ate","nat","bat"});
  Solution solu;
  auto ret = solu.groupAnagrams(anagram);
  return 0;
}
