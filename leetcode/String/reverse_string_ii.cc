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
  string reverseStr(string s, int k) {
      int size = s.size();
      int pos = 0;
      int processed_pos = 0;
      while (processed_pos < size) {
          if (processed_pos + 2*k <= size) {
              for (int i = pos, j = pos+k-1; i < j; ++i, --j) {
                  swap(s[i], s[j]);
              }
              pos += 2*k;
              processed_pos += 2*k;
              continue;
          }
          if (processed_pos + k > size) {
              for (int i = pos, j = size-1; i < j; ++i, --j) {
                  swap(s[i], s[j]);
              }
              processed_pos = size;
              pos = size;
              continue;
          }
          if (processed_pos + 2*k > size && processed_pos + k <= size) {
              for (int i = pos, j = pos+k-1; i < j; ++i, --j) {
                  swap(s[i], s[j]);
              }
              processed_pos = size;
              pos = size;
          }
      }
      return s;
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
