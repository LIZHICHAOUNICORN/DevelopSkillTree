// #include "glog/logging.h"
// #include "gflags/gflags.h"
#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        int size_num1 = nums1.size();
        int size_num2 = nums2.size();
        vector<int> & min_vec = size_num1 > size_num2 ? nums2 : nums1;
        vector<int> & max_vec = size_num1 > size_num2 ? nums1 : nums2;
        int i = 0, j = 0;
        for (; i < min_vec.size() && j < max_vec.size(); ) {
            if (min_vec[i] < max_vec[j]) {
                result.push_back(min_vec[i]);
                i += 1;
            } else if (min_vec[i] > max_vec[j]) {
                result.push_back(max_vec[j]);
                j += 1;
            } else if (min_vec[i] == max_vec[j]) {
                result.push_back(min_vec[i]);
                i += 1;
                result.push_back(max_vec[j]);
                j += 1;
            }
        }
        while (i < min_vec.size()) {
            result.push_back(min_vec[i]);
            ++i;
        }
        while (j < max_vec.size()) {
            result.push_back(max_vec[j]);
            ++j;
        }
        for (auto iter : result) {
          std::cout << iter << "\t" << std::endl;
        }
        double mid = 0;
        int len = size_num1 + size_num2;
        if (len % 2 == 1) {
            mid = static_cast<double> (result[len/2]);
        } else {
            int index = len/2;
            mid = static_cast<double>(result[index] + result[index-1]);
            mid = mid/2;
        }
        
        return mid;

    }
};

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  // gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> num1 ({1,2});
  vector<int> num2 ({3,4});
  Solution solu;
  double ret = solu.findMedianSortedArrays(num1, num2);
  std::cout << ret << std::endl;
  // LOG(INFO) << ret;
  return 0;
}
