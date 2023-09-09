#include <vector>
#include <random>

#include <glog/logging.h>
#include <gflags/gflags.h>


using namespace std;
// Problem: https://leetcode-cn.com/problems/random-pick-with-weight/
// Solutions: https://leetcode-cn.com/problems/random-pick-with-weight/solution/chi-xiao-dou-nojie-ti-python-dai-ni-du-d-7iev/

class Solution {
public:
    vector<int> a;
    int sum = 0;
    Solution(vector<int>& w) {
        int n = w.size();
        for(int i = 0;i<n;i++){
            sum += w[i];
            a.push_back(sum);
        }
    }
    int pickIndex() {
        std::mt19937 generator(random_device{}());
        std::uniform_int_distribution<int> distribution(1, sum);
        int dice_roll = distribution(generator);
        return lower_bound(a.begin(),a.end(), dice_roll) - a.begin();
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> weight({1,3});

  Solution solu(weight);
  int ret = solu.pickIndex();
  LOG(INFO) << "ret: " << ret;
  return 0;
}
