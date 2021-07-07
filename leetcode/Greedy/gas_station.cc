#include <vector>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::sort;

// 贪心
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int cur_sum = 0;
        int min = INT_MAX;
        for (int i = 0; i < gas.size(); ++i) {
            int rest = gas[i] - cost[i];
            cur_sum += rest;
            if (cur_sum < min) {
                min = cur_sum;
            }
        }
        if (cur_sum < 0) return -1;
        if (min >= 0) return 0;
        for (int i = gas.size()-1; i >= 0; --i) {
            int rest = gas[i] - cost[i];
            min += rest;
            if (min >= 0) return i;
        }
        return -1;
    }
};

// 贪心2
class Solution1 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int cur_sum = 0;
        int total_sum = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); ++i) {
            cur_sum += gas[i] - cost[i];
            total_sum += gas[i] - cost[i];
            if (cur_sum < 0) {
                start = i + 1;
                cur_sum = 0;
            }
        }
        if (total_sum < 0) return -1;
        return start;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
