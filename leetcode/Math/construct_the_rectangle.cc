#include <algorithm>
#include <climits>
#include <vector>
#include <cmath>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem:
// https://leetcode-cn.com/problems/construct-the-rectangle/

class Solution {
public:
    vector<int> constructRectangle(int area) {
        int w = sqrt(1.0 * area);
        while (area % w) {
            --w;
        }
        return {area / w, w};
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  vector<int> ret = solu.constructRectangle(4);
  for (const int & r : ret) {
    LOG(INFO) << r;
  }

  return 0;
}
