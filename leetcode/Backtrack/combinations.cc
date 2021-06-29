#include <vector>
#include <iostream>

using std::vector;

class Solution {
private:
    void backtrack(int n, int k, int start) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        for (int i = start; i <= n; ++i) {
            path.push_back(i);
            backtrack(n, k, i+1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> result;
    vector<int> path;
    vector<vector<int>> combine(int n, int k) {
        backtrack(n, k, 1);
        return result;
    }
};

class Solution1 {
private:
    void backtrack(int n, int k, int start) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        for (int i = start; i <= n - (k - path.size())+1; ++i) {
            path.push_back(i);
            backtrack(n, k, i+1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> result;
    vector<int> path;
    vector<vector<int>> combine(int n, int k) {
        backtrack(n, k, 1);
        return result;
    }
};




int main(int argc, char *argv[]) {
  Solution solu;
  vector<int> nums({1,1,1,1,1});
  return 0;
}
