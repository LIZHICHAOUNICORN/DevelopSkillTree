#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using std::vector;
using std::set;
/*
 * @lc app=leetcode.cn id=131 lang=cpp
 *
 * [131] 分割回文串
 */

class Solution {
public:
    vector<vector<string>> result;
    vector<string> path;
    void backtrace(const string& s, int start_index) {
        if (start_index >= s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = start_index; i < s.size(); ++i) {
            if (isPalindrome(s, start_index, i)) {
                string str = s.substr(start_index, i-start_index+1);
                path.push_back(str);
            } else {
                continue;
            }
            backtrace(s, i+1);
            path.pop_back();
        }
    }

    bool isPalindrome(const string& s, int start, int end) {
        for(int i = start, j = end; i < j; ++i, --j) {
            if (s[i] != s[j]) return false;
        }
        return true;
    }
    vector<vector<string>> partition(string s) {
        backtrace(s, 0);
        return result;
    }
};




int main(int argc, char *argv[]) {
  Solution solu;
  
  return 0;
}
