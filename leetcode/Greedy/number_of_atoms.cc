#include <vector>
#include <map>
#include <algorithm>
#include <string>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::vector;
using std::map
using std::string;

// 递归解法
class Solution {
    // https://zxi.mytechroad.com/blog/string/leetcode-726-number-of-atoms/
    // https://www.youtube.com/watch?v=6nQ2jfs7a7I
public:
    string countOfAtoms(const string& formula) {
        int i = 0;
        string ans;
        for (const auto& kv : countOfAtoms(formula, i)) {
            ans += kv.first;
            if (kv.second > 1) ans += std::to_string(kv.second);
        }
        return ans;
    }
private:    
    map<string, int> countOfAtoms(const string& formula, int& i) {
        map<string, int> counts;
        while (i != formula.length()) {
            // 在括号内就递归解决，然后返回后需要乘倍数
            if (formula[i] == '(') {                
                const auto& tmp_counts = countOfAtoms(formula, ++i);
                const int count = getCount(formula, i);
                for (const auto& kv : tmp_counts)
                    counts[kv.first] += kv.second * count;
            } else if (formula[i] == ')') {
                ++i;
                return counts;
            } else {
                // 非括号内，直接计算原子名称以及数字
                const string& name = getName(formula, i);
                counts[name] += getCount(formula, i);
            }
        }
        return counts;
    }
    
    string getName(const string& formula, int& i) {
        string name;
        while (isalpha(formula[i]) 
           && (name.empty() || islower(formula[i]))) name += formula[i++];
        return name;
    }
    
    int getCount(const string& formula, int& i) {
        string count_str;
        while (isdigit(formula[i])) count_str += formula[i++];
        return count_str.empty() ? 1 : std::stoi(count_str);
    }    
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  return 0;
}
