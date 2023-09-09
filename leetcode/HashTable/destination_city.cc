#include <string>
#include <unordered_map>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  string destCity(vector<vector<string>>& paths) {
    unordered_map<string, string> comes;
    for (auto& path : paths) {
      for (int i = 0; i < path.size() - 1; ++i) {
        comes[path[i]] = path[i + 1];
      }
    }
    for (auto& path : paths) {
      for (auto& p : path) {
        if (comes.count(p) == 0) return p;
      }
    }
    return paths.back().back();
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<vector<string>> test_case;
  vector<string> case1({"London", "New York"});
  vector<string> case2({"New York", "Lima"});
  vector<string> case3({"Lima", "Sao Paulo"});
  test_case.push_back(case1);
  test_case.push_back(case2);
  test_case.push_back(case3);

  Solution solu;
  string ret = solu.destCity(test_case);
  LOG(INFO) << ret;
  return 0;
}
