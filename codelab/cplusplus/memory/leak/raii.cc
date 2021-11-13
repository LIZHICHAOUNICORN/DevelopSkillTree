#include <cstring>
#include <iostream>

using namespace std;

class A {
 private:
  char *p;
  unsigned int p_size;

 public:
  A(unsigned int n = 1)  // 构造函数中分配内存空间
  {
    p = new char[n];
    p_size = n;
  };
  ~A()  // 析构函数中释放内存空间
  {
    if (p != NULL) {
      delete[] p;  // 删除字符数组
      p = NULL;    // 防止出现野指针
    }
  };
  char *GetPointer() { return p; };
};

void fun() {
  A ex(100);
  char *p = ex.GetPointer();
  strcpy(p, "Test");
  cout << p << endl;
}

// failed
void fun1() {
  A ex(100);
  A ex1 = ex;
  char *p = ex.GetPointer();
  strcpy(p, "Test");
  cout << p << endl;
}

int main() {
  fun();
  return 0;
}
