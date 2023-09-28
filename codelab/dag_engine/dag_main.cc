#include <algorithm>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  LOG(INFO) << "dag engine start";
  return 0;
}
