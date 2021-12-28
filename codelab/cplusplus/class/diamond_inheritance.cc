#include <algorithm>
#include <iostream>
#include <string>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

class B {
 public:
  int ib;
  char cb;

 public:
  B() : ib(0), cb('B') {}

  virtual void f() { cout << "B::f()" << endl; }
  virtual void Bf() { cout << "B::Bf()" << endl; }
};
class B1 : public B {
 public:
  int ib1;
  char cb1;

 public:
  B1() : ib1(11), cb1('1') {}

  virtual void f() { cout << "B1::f()" << endl; }
  virtual void f1() { cout << "B1::f1()" << endl; }
  virtual void Bf1() { cout << "B1::Bf1()" << endl; }
};
class B2 : public B {
 public:
  int ib2;
  char cb2;

 public:
  B2() : ib2(12), cb2('2') {}

  virtual void f() { cout << "B2::f()" << endl; }
  virtual void f2() { cout << "B2::f2()" << endl; }
  virtual void Bf2() { cout << "B2::Bf2()" << endl; }
};

class D : public B1, public B2 {
 public:
  int id;
  char cd;

 public:
  D() : id(100), cd('D') {}

  virtual void f() { cout << "D::f()" << endl; }
  virtual void f1() { cout << "D::f1()" << endl; }
  virtual void f2() { cout << "D::f2()" << endl; }
  virtual void Df() { cout << "D::Df()" << endl; }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  D* p = new D();
  p->f();
  p->f1();
  // p->g();
  // p->h();
  delete p;

  return 0;
}
