#include <cstring>
#include <iostream>
using namespace std;

size_t my_strlen(const char *str) {
  size_t length = 0;
  while (*str++) ++length;
  return length;
}

void size_of(char arr[]) {
  cout << sizeof(arr) << endl;  // warning: 'sizeof' on array function parameter
                                // 'arr' will return size of 'char*' .
  cout << strlen(arr) << endl;
}

int main(int argc, char *argv[]) {
  char *ptr = new char[strlen("hello") + 1];
  strcpy(ptr, "hello");
  size_t len = my_strlen(ptr);
  std::cout << "my strlen " << len << std::endl;
  delete ptr;

  char arr[20] = "hello";
  size_of(arr);
  return 0;
}
