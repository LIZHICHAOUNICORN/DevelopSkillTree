#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    for (string s : strs) {
      string t = s; 
      sort(t.begin(), t.end());
      mp[t].push_back(s);
    }
    vector<vector<string>> anagrams;
    for (auto p : mp) { 
      anagrams.push_back(p.second);
    }
    return anagrams;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
  Solution solu;
  vector<vector<string>> ret = solu.groupAnagrams(strs);
  LOG(INFO) << ret.size();
  return 0;
}
