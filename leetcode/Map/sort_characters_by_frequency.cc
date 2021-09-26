#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

// #include "third_party/glog/include/logging.h"
// #include "third_party/gflags/include/gflags.h"

using namespace std;

class Solution {
 private:
  struct {
    bool operator()(map<int, vector<int>>::iterator a,
                    map<int, vector<int>>::iterator b) const {
      return a->first < b->first;
    }
  } customLess;

 public:
  string frequencySort(string s) {
    map<char, int> count_char;
    map<int, vector<char>, std::greater<int>> sort_index;
    for (char c : s) {
      if (count_char.count(c)) {
        count_char[c] += 1;
      } else {
        count_char[c] = 1;
      }
    }
    for (auto iter = count_char.begin(); iter != count_char.end(); ++iter) {
      sort_index[iter->second].push_back(iter->first);
    }
    // sort(sort_index.begin(), sort_index.end(), customLess);

    string result;
    for (auto iter = sort_index.begin(); iter != sort_index.end(); ++iter) {
      for (int j = 0; j < iter->second.size(); ++j) {
        for (int i = 0; i < iter->first; ++i) {
          result.push_back(iter->second[j]);
        }
      }
    }
    return result;
  }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string query("abcc");
  string ret = solu.frequencySort(query);
  // LOG(INFO) << ret;
  cout << "result: " << ret << endl;

  return 0;
}
