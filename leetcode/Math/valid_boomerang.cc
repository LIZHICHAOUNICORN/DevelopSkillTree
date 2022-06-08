#include <type_traits>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        vector<int> v1 = {points[1][0] - points[0][0], points[1][1] - points[0][1]};
        vector<int> v2 = {points[2][0] - points[0][0], points[2][1] - points[0][1]};
        return v1[0] * v2[1] - v1[1] * v2[0] != 0;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<vector<int>> points;
  vector<int> p1 = {0, 0};
  points.emplace_back(p1);
  vector<int> p2 = {1, 1};
  points.emplace_back(p2);
  vector<int> p3 = {3, 3};
  points.emplace_back(p3);

  Solution solu;
  bool ret = solu.isBoomerang(points);
  LOG(INFO) << ret;

  return 0;
}
