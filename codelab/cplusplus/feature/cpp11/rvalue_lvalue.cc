#include <iostream>
using namespace std;

// g++  -fno-elide-constructors

int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;
class A {
 public:
  A() { cout << "construct: " << ++g_constructCount << endl; }

  A(const A& a) {
    cout << "copy construct: " << ++g_copyConstructCount << endl;
  }
  ~A() { cout << "destruct: " << ++g_destructCount << endl; }
};

A GetA() { return A(); }

class Base {
 public:
  Base() : m_ptr(new int(0)) { cout << "construct" << endl; }
  Base(const Base& b)
      : m_ptr(new int(*b.m_ptr))  //深拷贝的拷贝构造函数
  {
    cout << "copy construct" << endl;
  }
  ~Base() { delete m_ptr; }

 private:
  int* m_ptr;
};

Base GetBase() { return Base(); }

int main() {
  A a = GetA();

  Base b = GetBase();
  return 0;
}
