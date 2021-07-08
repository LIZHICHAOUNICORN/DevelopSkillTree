#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::sort;


class Solution {
private:
    static bool cmp(vector<int> a, vector<int> b) {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);
        int result = 1;
        for (int i = 1; i < points.size(); ++i) {
            if (points[i][0] > points[i-1][1]) {
                result++;
            } else {
                points[i][1] = min(points[i][1], points[i-1][1]);
            }
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
