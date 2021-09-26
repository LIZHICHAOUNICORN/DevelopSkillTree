#include <algorithm>
#include <array>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::array;

class ParkingSystem {
 private:
  array<int, 3> parking_;

 public:
  ParkingSystem(int big, int medium, int small) {
    parking_[0] = big;
    parking_[1] = medium;
    parking_[2] = small;
  }

  bool addCar(int carType) {
    if (carType > 3 || carType < 0) return false;
    if (parking_[carType - 1] > 0) {
      --parking_[carType - 1];
      return true;
    }
    return false;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  return 0;
}
