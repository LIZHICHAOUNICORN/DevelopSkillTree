#include <iostream>
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
using namespace std;

int main() {
  int var1 = 10, var2 = 100;
  cout << MAX(var1, var2) << endl;
  cout << MIN(var1, var2) << endl;
  return 0;
}
/*
程序运行结果：
100
10
*/
