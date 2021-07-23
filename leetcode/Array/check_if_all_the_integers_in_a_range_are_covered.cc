#include <vector>
#include <unordered_map>
#include <random>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
private:
    bool CheckCover(vector<int>& range, int target) {
        if (target >= range.front() && target <= range.back()) {
            return true;
        }
        return false;
    }
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        for (int i = left; i <= right; ++i) {
            bool cover = false;
            for (int j = 0; j < ranges.size(); ++j) {
                if (CheckCover(ranges[j], i)) {
                    cover = true;
                    break;
                }
            }
            if (!cover) return false;
        }
        return true;

    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
