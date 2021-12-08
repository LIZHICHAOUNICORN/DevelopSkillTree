#include <algorithm>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/ransom-note/

using namespace std;

class Solution {
 public:
  bool canConstruct(string ransomNote, string magazine) {
    if (ransomNote.size() > magazine.size()) {
      return false;
    }
    vector<int> cnt(26);
    for (auto& c : magazine) {
      cnt[c - 'a']++;
    }
    for (auto& c : ransomNote) {
      cnt[c - 'a']--;
      if (cnt[c - 'a'] < 0) {
        return false;
      }
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  string r("aa");
  string m("ab");

  Solution solu;
  auto ret = solu.canConstruct(r, m);
  LOG(INFO) << ret;

  return 0;
}
