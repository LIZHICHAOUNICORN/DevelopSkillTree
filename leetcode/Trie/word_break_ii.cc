#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problems: https://leetcode-cn.com/problems/word-break
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;

class Solution {
 private:
  unordered_map<int, vector<string>> ans;
  unordered_set<string> wordSet;

 public:
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    wordSet = unordered_set<string>(wordDict.begin(), wordDict.end());
    backtrack(s, 0);
    return ans[0];
  }

  void backtrack(const string& s, int index) {
    if (!ans.count(index)) {
      if (index == s.size()) {
        ans[index] = {""};
        return;
      }
      ans[index] = {};
      for (int i = index + 1; i <= s.size(); ++i) {
        string word = s.substr(index, i - index);
        if (wordSet.count(word)) {
          backtrack(s, i);
          for (const string& succ : ans[i]) {
            ans[index].push_back(succ.empty() ? word : word + " " + succ);
          }
        }
      }
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string s(
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  vector<string> wordDict({"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa",
                           "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"});
  auto ret = solu.wordBreak(s, wordDict);
  return 0;
}
