#include <algorithm>
#include <iostream>
#include <string>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Point
class Point {
 public:
  Point(float x) { x_ = x; }
  virtual ~Point() {}

  float getX() const {
    count_++;
    return x_;
  }

  static int getCount() { return count_; }

 protected:
  virtual int print(string& str) const {
    LOG(INFO) << str;
    return count_;
  }

 private:
  float x_;
  static int count_;
};

int Point::count_ = 0;

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Point* p = new Point(1.0);
  LOG(INFO) << p->getX();
  LOG(INFO) << p->getCount();
  delete p;

  return 0;
}
