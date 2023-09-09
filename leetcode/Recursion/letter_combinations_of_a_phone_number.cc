// Author: zhichaoli
// Time: 2020年02月13日

#include <map>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using std::map;
using std::vector;
using std::string;

// recursive backtracking
class Solution {
 public:
  vector<string> letterCombinations(string digits) {
    vector<string> ret;
    if (digits.empty()) return ret;
    map<char, vector<char>> relations;
    relations['2'] = {'a', 'b', 'c'};
    relations['3'] = {'d', 'e', 'f'};
    relations['4'] = {'g', 'h', 'i'};
    relations['5'] = {'j', 'k', 'l'};
    relations['6'] = {'m', 'n', 'o'};
    relations['7'] = {'p', 'q', 'r', 's'};
    relations['8'] = {'t', 'u', 'v'};
    relations['9'] = {'w', 'x', 'y', 'z'};
    string level;
    Helper(digits, 0, level, ret, relations);
    return ret;
  }

 private:
  void Helper(const string& digits, size_t cur, string& level,
              vector<string>& ret, map<char, vector<char>>& relations) {
    if (cur == digits.size()) {
      ret.push_back(level);
      return;
    }

    for (size_t j = 0; j < relations[digits[cur]].size(); ++j) {
      level.append(1u, relations[digits[cur]][j]);
      Helper(digits, cur + 1, level, ret, relations);
      level.erase(level.size() - 1);
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string digits("234");
  vector<string> ret = solu.letterCombinations(digits);
  return 0;
}
