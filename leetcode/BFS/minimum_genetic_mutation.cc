#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::map;
using std::set;
using std::vector;
using std::queue;
using std::string;
using std::pair;
using std::find;

class Solution {
 public:
  int minMutation(string start, string end, vector<string>& bank) {
    if (find(bank.begin(), bank.end(), end) == bank.end()) return -1;
    set<string> uniq_bank(bank.begin(), bank.end());
    queue<pair<string, int>> try_step;
    try_step.push(make_pair(start, 0));
    // the char match replace chars
    map<char, string> ralations;
    ralations['A'] = "TCG";
    ralations['T'] = "ACG";
    ralations['C'] = "ATG";
    ralations['G'] = "ATC";
    LOG(INFO) << "end: " << end;
    while (!try_step.empty()) {
      // notice: please use front, not back, because it's bfs.
      pair<string, int> step = try_step.front();
      DLOG(INFO) << "str: " << step.first << ", step: " << step.second;
      try_step.pop();
      if (step.first == end) return step.second;
      for (size_t i = 0; i < step.first.size(); ++i) {
        DLOG(INFO) << "i: " << i << ", v: " << step.first[i];
        for (char item : ralations[step.first[i]]) {
          string new_step = step.first.substr(0, i);
          new_step.append(1, item);
          new_step += step.first.substr(i + 1);
          DLOG(INFO) << "new step: " << new_step;
          auto index = find(uniq_bank.begin(), uniq_bank.end(), new_step);
          if (index != uniq_bank.end()) {
            DLOG(INFO) << "find: " << new_step;
            try_step.push(make_pair(new_step, step.second + 1));
            uniq_bank.erase(index);
          }
        }
      }
    }
    return -1;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string start("AAAACCCC");
  string end("CCCCCCCC");
  vector<string> bank = {"AAAACCCA", "AAACCCCA", "AACCCCCA", "AACCCCCC",
                         "ACCCCCCC", "CCCCCCCC", "AAACCCCC", "AACCCCCC"};
  int ret = solu.minMutation(start, end, bank);
  LOG(INFO) << ret;
  return 0;
}
