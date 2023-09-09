#include <string>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problems: https://leetcode-cn.com/problems/repeated-dna-sequences/

using namespace std;

class Solution {
 public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> ret;
    if (s.size() <= 10) return ret;

    unordered_map<string, int> cache;

    for (size_t i = 0; i <= s.size() - 10; ++i) {
      const string& sub = s.substr(i, 10);
      if (cache.count(sub) > 0 && cache[sub] == 1) {
        ret.push_back(sub);
      }
      ++cache[sub];
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string test_case("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");

  Solution solu;
  auto ret = solu.findRepeatedDnaSequences(test_case);
  LOG(INFO) << ret.back();
  return 0;
}
