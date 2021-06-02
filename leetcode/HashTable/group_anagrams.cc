#include <algorithm>
#include <unordered_set>
#include <vector>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    if (strs.empty()) return vector<vector<string>>();
    vector<string> strs_copy = strs;
    for (size_t i = 0; i < strs.size(); ++i) {
      sort(strs[i].begin(), strs[i].end());
    }
    vector<vector<string>> ret;
    unordered_set<int> index;
    for(size_t j = 0; j < strs.size(); ++j) {
      if (index.find(j) != index.end()) continue;
      index.insert(j);
      vector<string> dup;
      dup.push_back(strs_copy[j]);
      for (size_t k = j+1; k < strs.size(); ++k) {
        if (strs[j] == strs[k]) {
          dup.push_back(strs_copy[k]);
          index.insert(k);
        }
      }
      ret.push_back(dup);        
    }
    return ret;
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<string> test_case = {"eat","tea","tan","ate","nat","bat"};
  Solution solu;
  vector<vector<string>> ret = solu.groupAnagrams(test_case);
  return 0;
}
