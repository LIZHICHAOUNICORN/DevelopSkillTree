#include <algorithm>
#include <queue>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  std::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  LOG(INFO) << q.size();

  while (!q.empty()) {
    LOG(INFO) << "queue front " << q.front()
              << ", queue back: " << q.back();
    q.pop();
  }

  return 0;
}
