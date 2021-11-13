#include <iostream>

using namespace std;
/* 函数模板和类模板的区别？
 *
 * 实例化方式不同：函数模板实例化由编译程序在处理函数调用时自动完成，类模板实例化需要在程序中显式指定。
 * 实例化的结果不同：函数模板实例化后是一个函数，类模板实例化后是一个类。
 * 默认参数：类模板在模板参数列表中可以有默认参数。
 * 特化：函数模板只能全特化；而类模板可以全特化，也可以偏特化。
 * 调用方式不同：函数模板可以隐式调用，也可以显式调用；类模板只能显式调用。
 *
 */

template <typename T>
T add_fun(const T& tmp1, const T& tmp2) {
  return tmp1 + tmp2;
}

template <typename T>
class Complex {
 public:
  //构造函数
  Complex(T a, T b) {
    this->a = a;
    this->b = b;
  }

  //运算符重载
  Complex<T> operator+(Complex& c) {
    Complex<T> tmp(this->a + c.a, this->b + c.b);
    cout << tmp.a << " " << tmp.b << endl;
    return tmp;
  }

 private:
  T a;
  T b;
};

// 可变参数
template <typename T>
void print_fun(const T& t) {
  cout << t << endl;  // 最后一个元素
}

template <typename T, typename... Args>
void print_fun(const T& t, const Args&... args) {
  cout << t << " ";
  print_fun(args...);
}

#include <cstring>
#include <iostream>

using namespace std;
//函数模板
template <class T>
bool compare(T t1, T t2) {
  cout << "通用版本：";
  return t1 == t2;
}

template <>  //函数模板特化
bool compare(char* t1, char* t2) {
  cout << "特化版本：";
  return strcmp(t1, t2) == 0;
}

int main(int argc, char* argv[]) {
  int var1, var2;
  cin >> var1 >> var2;
  cout << add_fun(var1, var2);

  double var3, var4;
  cin >> var3 >> var4;
  cout << add_fun(var3, var4);

  Complex<int> a(10, 20);
  Complex<int> b(20, 30);
  Complex<int> c = a + b;

  // 模板可变参数
  print_fun("Hello", "wolrd", "!");

  // 模板参数特化
  char arr1[] = "hello";
  char arr2[] = "abc";
  cout << compare(123, 123) << endl;
  cout << compare(arr1, arr2) << endl;
  return 0;
}
