#include <algorithm>
#include <set>
#include <unordered_set>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  LOG(INFO) << "Iteration set";
  std::set<int> myset({3, 1, 4, 1, 5, 9, 2, 6, 5});
  std::for_each(myset.cbegin(), myset.cend(), [](int x) { LOG(INFO) << x; });

  LOG(INFO) << "Iteration unordered_set";
  std::unordered_set<int> h_set({3, 1, 4, 1, 5, 9, 2, 6, 5});
  std::for_each(h_set.cbegin(), h_set.cend(), [](int x) { LOG(INFO) << x; });

  return 0;
}
