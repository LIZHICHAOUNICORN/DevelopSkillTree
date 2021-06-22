#include <vector>
#include <iostream>
#include <string>
 

using std::vector;
using std::string;

class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> ans;
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                if (__builtin_popcount(h) + __builtin_popcount(m) == turnedOn) {
                    ans.push_back(std::to_string(h) + ":" + (m < 10 ? "0" : "") + std::to_string(m));
                }
            }
        }
        return ans;
    }
};

int main(int argc, char* argv[]) {
  Solution solu;
  vector<string> ret = solu.readBinaryWatch(2);
  for (auto i : ret) {
    std::cout << i << std::endl;
  }
  return 0;
}
