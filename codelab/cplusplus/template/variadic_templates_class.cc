/*
 * 对模板可变参数的实验
*/
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

//1. 模版偏特化和递归方式来展开参数包

//前向声明
template <typename... Args>
struct Sum;

//基本定义
template <typename First, typename... Rest>
struct Sum<First, Rest...> {
  enum { value = Sum<First>::value + Sum<Rest...>::value };
};

//递归终止
template <typename Last>
struct Sum<Last> {
  enum { value = sizeof(Last) };
};

// 2. 继承方式展开参数包
//整型序列的定义
template <int...>
struct IndexSeq {};

//继承方式，开始展开参数包
template <int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

// 模板特化，终止展开参数包的条件
template <int... Indexes>
struct MakeIndexes<0, Indexes...> {
  typedef IndexSeq<Indexes...> type;
};

int main(int argc, char* argv[]) {
  cout << "Sum: " << Sum<int, double, short>::value << endl;

  using T = MakeIndexes<3>::type;
  cout << typeid(T).name() << endl;

  return 0;
}
