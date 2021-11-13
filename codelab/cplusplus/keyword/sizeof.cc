#include <iostream>
using namespace std;

// C语言没有布尔类型，因此按整数, 4个字节
// C++有布尔类型，占1字节

int main() {
    cout << sizeof(1==1) << endl;
    return 0;
}

/*
1
*/
