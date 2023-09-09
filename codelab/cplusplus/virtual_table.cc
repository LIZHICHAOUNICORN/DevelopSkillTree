#include <iostream>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

class Base {
 public:
  virtual void fun() { cout << "Base::fun()" << endl; }

  virtual void fun1() { cout << "Base::fun1()" << endl; }

  virtual void fun2() { cout << "Base::fun2()" << endl; }
};

class Derive : public Base {
 public:
  void fun() { cout << "Derive::fun()" << endl; }

  virtual void D_fun1() { cout << "Derive::D_fun1()" << endl; }

  virtual void D_fun2() { cout << "Derive::D_fun2()" << endl; }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Base *p = new Derive();
  p->fun();  // Derive::fun() 调用派生类中的虚函数
  return 0;
}
