#include <cstdlib>
#include <random>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Solution {
 public:
  void backtracking(string& S, string& path, int index, vector<string>& ret,
                    vector<bool>& used) {
    if (path.size() == S.size()) {
      ret.push_back(path);
      return;
    }
    for (int i = 0; i < S.size(); ++i) {
      if (!used[i]) {
        if (i > 0 && S[i] == S[i - 1] && used[i - 1] == false) {
          continue;
        }
        used[i] = true;
        path.push_back(S[i]);
        backtracking(S, path, index + 1, ret, used);
        used[i] = false;
        path.pop_back();
      }
    }
  }
  vector<string> permutation(string S) {
    vector<string> ret;
    sort(S.begin(), S.end());
    string path;
    vector<bool> used(S.size(), false);
    backtracking(S, path, 0, ret, used);
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  random_device rd;
  int array_value[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  vector<int> input_value(array_value,
                          array_value + sizeof(array_value) / sizeof(int));
  int ret = 0;
  ret = most_water_v2(input_value);
  LOG(INFO) << "result: " << ret;
  return ret;
}
