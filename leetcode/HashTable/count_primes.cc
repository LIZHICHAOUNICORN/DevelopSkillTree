#include <unordered_map>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using namespace std;

class Solution {
 public:
  int countPrimes(int n) {
  // Sieve of Erantothoses
  vector<bool> check(n+1,true);

  // Because 0 and 1 are not primes
  check[0]=false;
  check[1]=false;

  // OPtimization 2: Do only  rootn since all numbers after that are handled
  // The remaining values are already true
  for (int i = 2; i*i <= n; i++) {
    // If already visited
    if (check[i] == false) continue;

    // Optimation 1 : 3*2 is already handled by 2*3.  directly start from 9
    int j = i*i;
    while (j <= n) {
      check[j] = false;
      j = j+i;
    }
  }

  int count=0;
  // Checking all the numbers which are prime (less than n)
  for (int i = 1; i < n; i++) {
    if (check[i]) count++;
  }

  return count;
}
};


// Time Limit Exceeded
class Solution {
public:
  int countPrimes(int n) {
    int ret = 0;
    for (size_t i = 2; i < n; ++i) {
      if (IsPrime(i)) ++ret;
    }
    return ret;
  }
 private:
  bool IsPrime(size_t n) {
    for (size_t i = 2; i*i <= n; ++i) {
      if (n % i == 0) return false;
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  vector<int> test_cast = {2,7,11,15};
  Solution solu;
  int ret = solu.countPrimes(9);
  LOG(INFO) << ret;
  return 0;
}
