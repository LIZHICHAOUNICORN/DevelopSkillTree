#include <iostream>
#include <chrono>

#include <gflags/gflags.h>
#include <glog/logging.h>
 
int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
 
  std::chrono::seconds sec = std::chrono::duration_cast< std::chrono::seconds >(
        std::chrono::system_clock::now().time_since_epoch()
  );
 
  std::cout << sec.count() << std::endl;
  return 0;
}
