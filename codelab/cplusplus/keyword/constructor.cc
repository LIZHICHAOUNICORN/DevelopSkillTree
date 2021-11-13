#include <iostream>
using namespace std;

class A
{
public:
    A() = default; // 表示使用默认的构造函数
    ~A() = default; // 表示使用默认的析构函数
    A(const A &) = delete; // 表示类的对象禁止拷贝构造
    A &operator=(const A &) = delete; // 表示类的对象禁止拷贝赋值
};
int main(int argc, char *argv []) {
    A ex1;
    // A ex2 = ex1; // error: use of deleted function 'A::A(const A&)'
    A ex3;
    // ex3 = ex1; // error: use of deleted function 'A& A::operator=(const A&)'
    return 0;
}
