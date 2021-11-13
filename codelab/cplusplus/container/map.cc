#include <algorithm>
#include <map>
#include <unordered_map>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

void UpperBoundCase() {
  // initialize container
  map<int, int> mp;

  // insert elements in random order
  mp.insert({12, 30});
  mp.insert({11, 10});
  mp.insert({15, 50});
  mp.insert({14, 40});

  // when 11 is present
  auto it = mp.upper_bound(11);
  LOG(INFO) << "The upper bound of key 11 is " << (*it).first << " "
            << (*it).second;

  // when 13 is not present
  it = mp.upper_bound(13);
  LOG(INFO) << "The upper bound of key 13 is " << (*it).first << " "
            << (*it).second;

  // when 17 is exceeds the maximum key, so size
  // of mp is returned as key and value as 0.
  it = mp.upper_bound(17);
  LOG(INFO) << "The upper bound of key 17 is " << (*it).first << " "
            << (*it).second;
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  // upper_bound method
  UpperBoundCase();

  return 0;
}
