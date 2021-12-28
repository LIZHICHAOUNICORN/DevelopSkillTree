#include <algorithm>
#include <iostream>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// 虚函数
class A {
 public:
  virtual void v_fun()  // 虚函数
  {
    cout << "A::v_fun()" << endl;
  }
};

class B : public A {
 public:
  void v_fun() { cout << "B::v_fun()" << endl; }
};

// 被继承的基类的析构函数应该定义为虚函数
class Base {
 public:
  int baseData;
  ~Base() {}
};

class Derived : public Base {
 public:
  int derivedData;
};

// 虚函数的实现机制
class BaseClass {
 public:
  virtual void B_fun1() { cout << "Base::B_fun1()" << endl; }
  virtual void B_fun2() { cout << "Base::B_fun2()" << endl; }
  virtual void B_fun3() { cout << "Base::B_fun3()" << endl; }
};

class Derive : public BaseClass {
 public:
  virtual void D_fun1() { cout << "Derive::D_fun1()" << endl; }
  virtual void D_fun2() { cout << "Derive::D_fun2()" << endl; }
  virtual void D_fun3() { cout << "Derive::D_fun3()" << endl; }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  A* p = new B();
  p->v_fun();  // B::v_fun()

  // 内存泄漏

  Base* b = new Derived();
  delete b;  // 由于 Base 的析构函数不是虚函数，
             // 这里调用的是 Base 的析构函数，
             // 而非 Derived 的析构函数,
             // 因此，Derived 里的 derivedData 没有被释放，
             // 因此，内存泄漏。

  // 虚函数表
  Derive* ptr = new Derive();
  ptr->B_fun1();  // Base::B_fun1()
  delete ptr;

  return 0;
}
