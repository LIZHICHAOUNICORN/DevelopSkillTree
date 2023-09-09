#include <set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// #include <gperftools/profiler.h>
// Problem: https://leetcode-cn.com/problems/task-scheduler/

using namespace std;

class Solution {
 public:
  int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char ch : tasks) {
      ++freq[ch];
    }

    // 最多的执行次数
    int maxExec =
        max_element(freq.begin(), freq.end(), [](const auto& u, const auto& v) {
          return u.second < v.second;
        })->second;
    // 具有最多执行次数的任务数量
    int maxCount = accumulate(
        freq.begin(), freq.end(), 0,
        [=](int acc, const auto& u) { return acc + (u.second == maxExec); });

    return max((maxExec - 1) * (n + 1) + maxCount,
               static_cast<int>(tasks.size()));
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<char> tasks({"A", "A", "A", "B", "B", "B"});

  Solution solu;
  int ret = solu.leastInterval(tasks, 2);
  LOG(INFO) << ret;

  return 0;
}
