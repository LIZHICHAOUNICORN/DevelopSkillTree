#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
 public:
  bool checkRecord(string s) {
    int absent_count = 0;
    int cns_late = 0;
    for (auto& it : s) {
      if (it == 'L' || it == 'A') {
        if (it == 'L') {
          ++cns_late;
          if (cns_late >= 3) return false;
        } else {
          ++absent_count;
          cns_late = 0;
        }
      } else {
        cns_late = 0;
      }
    }
    if (cns_late >= 3 || absent_count >= 2) return false;
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
  Solution solu;
  vector<vector<string>> ret = solu.groupAnagrams(strs);
  LOG(INFO) << ret.size();
  return 0;
}
