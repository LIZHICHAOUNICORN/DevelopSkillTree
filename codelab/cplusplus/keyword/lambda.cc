#include <algorithm>
#include <iostream>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

/*
 * [capture list] (parameter list) -> return type
 * {
 *    function body;
 * };
 */

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  int arr[4] = {4, 2, 3, 1};
  //对 a 数组中的元素进行升序排序
  sort(arr, arr + 4, [=](const int& x, const int& y) -> bool { return x < y; });
  for (int n : arr) {
    cout << n << " ";
  }
  cout << endl;

  return 0;
}
