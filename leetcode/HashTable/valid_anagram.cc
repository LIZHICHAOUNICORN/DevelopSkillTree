#include <string>
#include <unordered_map>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    unordered_map<char, int> word;
    for (size_t i = 0; i < s.size(); ++i) {
      if (word.find(s[i]) != word.end()) {
        ++word[s[i]];
      } else {
        word[s[i]] = 1;
      }
    }
    for (size_t k = 0; k < t.size(); ++k) {
      if (word.find(t[k]) == word.end()) return false;
      --word[t[k]];
      if (word[t[k]] < 0) return false;
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  bool ret = solu.isAnagram("anagram", "nagaram");
  LOG(INFO) << "result: " << ret;
  return 0;
}
