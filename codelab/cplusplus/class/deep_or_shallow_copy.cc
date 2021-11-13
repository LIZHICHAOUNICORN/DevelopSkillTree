#include <iostream>

using namespace std;

// Shallow
class Test {
 private:
  int *p;

 public:
  Test(int tmp) {
    this->p = new int(tmp);
    cout << "Test(int tmp)" << endl;
  }
  ~Test() {
    if (p != NULL) {
      delete p;
    }
    cout << "~Test()" << endl;
  }
};

// Deep copy
class DeepTest {
 private:
  int *p;

 public:
  DeepTest(int tmp) {
    p = new int(tmp);
    cout << "Test(int tmp)" << endl;
  }
  ~DeepTest() {
    if (p != NULL) {
      delete p;
    }
    cout << "~Test()" << endl;
  }
  DeepTest(const DeepTest &tmp)  // 定义拷贝构造函数
  {
    p = new int(*tmp.p);
    cout << "Test(const Test &tmp)" << endl;
  }
};

int main(int argc, char *argv[]) {
  DeepTest ex1(10);
  DeepTest ex2 = ex1;

  // core dump, double free pointer.
  Test tex1(10);
  Test tex2 = tex1;
  return 0;
}
