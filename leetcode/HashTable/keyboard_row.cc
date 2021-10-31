#include <string>
#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/keyboard-row/

using namespace std;

// Hashtable
class Solution {
 public:
  vector<string> findWords(vector<string>& words) {
    vector<string> ans;
    string rowIdx = "12210111011122000010020202";
    for (auto& word : words) {
      bool isValid = true;
      char idx = rowIdx[tolower(word[0]) - 'a'];
      for (int i = 1; i < word.size(); ++i) {
        if (rowIdx[tolower(word[i]) - 'a'] != idx) {
          isValid = false;
          break;
        }
      }
      if (isValid) {
        ans.emplace_back(word);
      }
    }
    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> words({"Hello", "Alaska", "Dad", "Peace"});

  Solution solu;
  auto ret = solu.findWords(words);
  LOG(INFO) << ret.back();
  return 0;
}
