/*
 * 对模板可变参数的实验
*/
#include <iostream>

using namespace std;

// 简单示例
template <class... T>
void f(T... args) {
  cout << sizeof...(args) << endl;  //打印变参的个数
}

//递归终止函数，空参数
void print() { cout << "empty" << endl; }

//展开函数
template <class T, class... Args>
void print(T head, Args... rest) {
  cout << "parameter " << head << endl;
  print(rest...);
}

// 递归终止函数, 单个参数
template <typename T>
T sum(T t) {
  return t;
}
template <typename T, typename... Types>
T sum(T first, Types... rest) {
  cout << "sum  parameter size: " << sizeof...(rest) << endl;
  return first + sum<T>(rest...);
}

// 逗号表达式展开参数包
template <class T>
void printarg(T t)
{
   cout << t << endl;
}

template <class ...Args>
void expand(Args... args)
{
   int arr[] = {(printarg(args), 0)...};
}


int main(int argc, char* argv[]) {
  f();            // 0
  f(1);           // 1
  f(1, 2);        // 2
  f(1, 2.5, "");  // 3

  print(1, 2, 3, 4);

  int num_sum = sum(1, 2, 3, 4);  // 10
  cout << "num_sum : " << num_sum << endl;
  
  expand(1,2,3,4);
  return 0;
}
