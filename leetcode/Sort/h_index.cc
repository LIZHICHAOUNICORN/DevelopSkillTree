#include <stack>
#include <vector>

#include "./tree_node.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;
class Solution {
 public:
  int hIndex(vector<int>& citations) {
    sort(citations.begin(), citations.end());
    int h = 0, i = citations.size() - 1;
    while (i >= 0 && citations[i] > h) {
      h++;
      i--;
    }
    return h;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  return 0;
}
