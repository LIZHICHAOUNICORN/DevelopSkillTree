#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/lru-cache/

class LRUCache {
 private:
 public:
  LRUCache(int capacity) {}
  bool put(int key, int value) {}
  int get(int key) {}
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}