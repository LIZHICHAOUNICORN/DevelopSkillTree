#include <iostream>
using namespace std;

class A
{
private:
    int val;

public:
    A(int tmp) : val(tmp) // 带参数构造函数
    {
        cout << "A(int tmp)" << endl;
    }

    A(const A &tmp) // 拷贝构造函数
    {
        cout << "A(const A &tmp)" << endl;
        val = tmp.val;
    }

    A &operator=(const A &tmp) // 赋值函数（赋值运算符重载）
    {
        cout << "A &operator=(const A &tmp)" << endl;
        val = tmp.val;
        return *this;
    }

    void fun(A tmp)
    {
    }
};

int main()
{
    A ex1(1);
    A ex2(2);
    A ex3 = ex1;
    ex2 = ex1;
    ex2.fun(ex1);
    return 0;
}
/*
运行结果：
A(int tmp)
A(int tmp)
A(const A &tmp)
A &operator=(const A &tmp)
A(const A &tmp)
*/

