#include <map>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  bool isIsomorphic(std::string s, std::string t) {
    if (s.size() != t.size()) return false;
    
    std::map<char, char> ma;
    std::map<char, char> mb;
    
    for (size_t i = 0; i < s.size(); i++) {
      ma[s[i]] = t[i];
      mb[t[i]] = s[i];
    }
    
    for (size_t i = 0; i < s.size(); i++) {
      if (ma[s[i]] != t[i] || mb[t[i]] != s[i]) {
            return false;
      }
    }
    
    return true; 
  }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> test_cast = {2,7,11,15};
  Solution solu;
  string s = "add";
  string t = "egg";
  bool ret = solu.isIsomorphic(s, t);
  LOG(INFO) << ret;
  return 0;
}
