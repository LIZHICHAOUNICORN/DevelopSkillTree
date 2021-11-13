#include <iostream>
#include <utility>
#include <list>
#include <string>
using namespace std;

// 如果不用std::move，拷贝的代价很大，性能较低。使用move几乎没有任何代价，只是转换了资源的所有权。
// 他实际上将左值变成右值引用，然后应用移动语义，调用移动构造函数，就避免了拷贝，提高了程序性能。
// 如果一个对象内部有较大的对内存或者动态数组时，很有必要写move语义的拷贝构造函数和赋值函数，
// 避免无谓的深拷贝，以提高性能。事实上，C++11中所有的容器都实现了移动语义，方便我们做性能优化。

std::list< std::string> tokens;
//省略初始化...
std::list< std::string> copy_t = tokens; //这里存在拷贝 

std::list< std::string> move_t = std::move(tokens);  //这里没有拷贝



void processValue(int& a) { cout << "lvalue" << endl; }
void processValue(int&& a) { cout << "rvalue" << endl; }

template <typename T>
void forwardValue(T&& val) {
  processValue(std::forward<T>(val));  //照参数本来的类型进行转发。
}

void Testdelcl() {
  int i = 0;
  forwardValue(i);  //传入左值
  forwardValue(0);  //传入右值
}

int main() {
  Testdelcl();

  return 0;
}
