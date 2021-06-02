#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

#include "glog/logging.h"
#include "gflags/gflags.h"

#include <gperftools/profiler.h>

DEFINE_int32(input_size, 10, "input data size");
DEFINE_int32(epolls, 100, "input data size");
DEFINE_string(porf_file, "move_zeroes.porf", "");

using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    for(int i=0; i<n; i++) {
        for(int j=i; j<n; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
    
    for(int i=0; i<n; i++) {
      std::reverse(matrix[i].begin(), matrix[i].end());
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
