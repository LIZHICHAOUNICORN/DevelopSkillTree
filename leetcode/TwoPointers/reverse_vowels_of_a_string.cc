#include <iostream>
#include <vector>
#include <stack>

// #include "glog/logging.h"
// #include "gflags/gflags.h"

using namespace std;

// TowPointer. Time: O(n), Space: O(1)
class Solution {
public:
    string reverseVowels(string s) {
        int l = 0;
        int r = s.size() -1;
        set<char> vowels({'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'});
        while (l < r) {
            while(l < r && vowels.count(s[l]) == 0) {
                ++l;
            }
            while (r > l && vowels.count(s[r]) == 0) {
                --r;
            }
            swap(s[l], s[r]);
            ++l;
            --r;
        }
        return s;
    }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  vector<int> height({1,8,6,2,5});
  int ret = solu.maxArea(height);
  cout << ret << endl;
  
  return 0;
}
