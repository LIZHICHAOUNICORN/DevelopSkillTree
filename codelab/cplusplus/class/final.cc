#include <iostream>

using namespace std;

class BaseClass final {};

// error: cannot derive from 'final' base 'Base'
// in derived type 'Derive'
// class Derive : public BaseClass {};


// 借助友元以及虚继承

template <typename T>
class Base {
  friend T;

 private:
  Base() { cout << "base" << endl; }
  ~Base() {}
};

class B : virtual public Base<B> {  //一定注意 必须是虚继承
 public:
  B() { cout << "B" << endl; }
};


//class C : public B {
// public:
//  C() {
//  }  // error: 'Base<T>::Base() [with T = B]' is private within this context
//};

int main(int argc, char *argv[]) {
  // final 关键字
  BaseClass ex;
  cout << sizeof(ex) << endl;
  // 借助友元以及虚继承
  B b;
  cout << sizeof(b) << endl;
  return 0;
}
