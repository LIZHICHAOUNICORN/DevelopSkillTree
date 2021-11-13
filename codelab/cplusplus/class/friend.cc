#include <cassert>
#include <iostream>

using namespace std;

class Aclass {
  // 声明为类的友元函数
  friend ostream &operator<<(ostream &_cout, const Aclass &tmp);

 public:
  Aclass(int tmp) : var(tmp) {}

 private:
  int var;
};

ostream &operator<<(ostream &_cout, const Aclass &tmp) {
  _cout << tmp.var;
  return _cout;
}

class A {
  friend class B;

 public:
  A() : var(10) {}
  A(int tmp) : var(tmp) {}
  void fun() { cout << "fun():" << var << endl; }

 private:
  int var;
};

class B {
 public:
  B() {}
  void fun() {
    cout << "fun():" << ex.var << endl;  // 访问类 A 中的私有成员
  }

 private:
  A ex;
};

int main(int argc, char *argv[]) {
  // 访问数据成员, 4
  Aclass ex(4);
  cout << ex << endl;
  // 类间共享数据
  B bex;
  bex.fun();  // fun():10
  return 0;
}
