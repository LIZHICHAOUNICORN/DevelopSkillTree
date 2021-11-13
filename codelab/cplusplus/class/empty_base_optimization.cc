#include <cassert>
#include <iostream>
using namespace std;

class EmptyClass {};

class OtherClass {
  EmptyClass vA;
  int x;
};

// EBO
class BaseClassA {
  using Int = int;
  typedef double Double;
  enum class Config : uint8_t { Timeout = 1 };
  void foo() {}
  static int globalVal;
};

class DerivedClass : public BaseClassA {
  int x;
};

// struct
struct Base {};  // 空类

struct Derived1 : Base {
  int i;
};

struct Contain {
  Base b;
  int i;
};

int main(int argc, char* argv[]) {
  // 任何空类类型的对象大小至少为 1
  assert(sizeof(Base) > 0);

  // 应用空基优化
  assert(sizeof(Derived1) == sizeof(int));

  //继承与内含对比
  cout << "包含 empty struct" << sizeof(Contain) << endl;   // 8 byte
  cout << "继承empty struct " << sizeof(Derived1) << endl;  // 4 byte

  // 使用组合将导致类内存暴增
  cout << "empty class " << sizeof(EmptyClass) << endl;
  cout << "组合关系" << sizeof(OtherClass) << endl;

  // 使用空基类压缩优化技术
  cout << "Base class" << sizeof(BaseClassA) << endl;
  cout << "EBO derived class" << sizeof(DerivedClass) << endl;
}
