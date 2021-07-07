#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::sort;

class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> cy(ratings.size(), 1);
        for (int i = 1; i < ratings.size();++i) {
            if (ratings[i] > ratings[i-1]) cy[i] = cy[i-1]+1;
        }
        for (int j = ratings.size()-2; j >= 0; --j) {
            if (ratings[j] > ratings[j+1]) cy[j] = max(cy[j+1]+1, cy[j]);
        }
        int result = 0;
        for (int k = 0; k < ratings.size(); ++k) {
            result += cy[k];
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
