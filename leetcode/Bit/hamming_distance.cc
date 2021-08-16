#include <vector>
#include <iostream>
using std::vector;

class Solution {
public:
    int hammingDistance(int x, int y) {
        vector<int> x_bit(32, 0);
        vector<int> y_bit(32, 0);
        int ret = 0;
        int bit = 0;
        for (int i = 0; i < 32 && bit <= x; ++i) {
            bit = 1 << i;
            if (x & bit) x_bit[i] = 1; 
        }
        bit = 0;
        for (int i = 0; i < 32 && bit <= y; ++i) {
            int bit = 1 << i;
            if (y & bit) y_bit[i] = 1; 
        }
        for (int i = 0; i < 32; ++i) {
            if (x_bit[i] != y_bit[i]) {
                ret += 1;
            }
        }
        return ret;

    }
};

int main(int argc, char* argv[]) {
  Solution solu;
  int ret =  solu.hammingDistance(3, 1);
  std::cout << ret << std::endl;

}
