#include <iostream>
using namespace std;

// const cast
void TestConstCast() {
  // 原始数组
  int ary[4] = {1, 2, 3, 4};

  // 打印数据
  for (int i = 0; i < 4; i++) std::cout << ary[i] << "\t";
  std::cout << std::endl;

  // 常量化数组指针
  const int *c_ptr = ary;

  // 强制去掉常量属性，不能用于去掉变量的常量性，只能用于去除指针或引用的常量性，
  // 将常量指针转化为非常量指针或者将常量引用转化为非常量引用
  // （注意：表达式的类型和要转化的类型是相同的）。
  // 通过const_cast<Ty> 去常量
  int *ptr = const_cast<int *>(c_ptr);

  // 修改数据
  for (int i = 0; i < 4; i++) ptr[i] += 1;  // pass

  // 打印修改后的数据
  for (int i = 0; i < 4; i++) std::cout << ary[i] << "\t";
  std::cout << std::endl;
}

// static cast
/* class 的上下行转换 */
class Base {
  // something
};
class Sub : public Base {
  // something
};

void TestStaticCast() {
  /* 常规的使用方法 */
  float f_pi = 3.141592f;
  int i_pi = static_cast<int>(f_pi);  /// i_pi 的值为 3

  //上行 Sub -> Base
  //编译通过，安全
  Sub sub;
  Base *base_ptr = static_cast<Base *>(&sub);

  //下行 Base -> Sub
  //编译通过，不安全
  Base base;
  Sub *sub_ptr = static_cast<Sub *>(&base);
}

// dynamic_cast
class DBase {
 public:
  DBase() {}
  ~DBase() {}
  void print() { std::cout << "I'm DBase" << endl; }

  virtual void i_am_virtual_foo() {}
};

class DSub : public DBase {
 public:
  DSub() {}
  ~DSub() {}
  void print() { std::cout << "I'm DSub" << endl; }

  virtual void i_am_virtual_foo() {}
};

void TestDynamicCast() {
  cout << "DSub->DBase" << endl;
  DSub *sub = new DSub();
  sub->print();
  DBase *sub2base = dynamic_cast<DBase *>(sub);
  if (sub2base != nullptr) {
    sub2base->print();
  }
  cout << "<sub->base> sub2base val is: " << sub2base << endl;

  cout << endl << "Base->Sub" << endl;
  DBase *base = new DBase();
  base->print();
  DSub *base2sub = dynamic_cast<DSub *>(base);
  if (base2sub != nullptr) {
    base2sub->print();
  }
  cout << "<base->sub> base2sub val is: " << base2sub << endl;

  delete sub;
  delete base;
}

// g++ -fpermissive
// reinterpret_cast
void TestReinterpretCast() {
  int *ptr = new int(233);
  // uint32_t ptr_addr = reinterpret_cast<uint32_t>(ptr);
  cout << "ptr 的地址: " << hex << ptr << endl;
  // cout << "ptr_addr 的值(hex): " << hex << ptr_addr << endl;
  delete ptr;
}

int main() {
  TestConstCast();
  TestStaticCast();
  TestDynamicCast();
  TestReinterpretCast();

  return 0;
}
