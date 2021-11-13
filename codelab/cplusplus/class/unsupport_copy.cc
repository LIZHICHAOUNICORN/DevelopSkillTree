#include <algorithm>
#include <iostream>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class Uncopyable
{
public:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable &);            // 拷贝构造函数
    Uncopyable &operator=(const Uncopyable &); // 赋值构造函数
};
class A : private Uncopyable // 注意继承方式
{ 
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);


  return 0;
}
