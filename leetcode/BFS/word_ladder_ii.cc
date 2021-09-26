#include <algorithm>
#include <cassert>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using std::vector;
using std::queue;
using std::string;
using std::pair;
using std::unordered_map;
using std::find;

/// BFS
/// Time Complexity: O(n*n)
/// Space Complexity: O(n)
class Solution {
 public:
  vector<vector<string>> findLadders(string beginWord, string endWord,
                                     vector<string>& wordList) {
    int end =
        find(wordList.begin(), wordList.end(), endWord) - wordList.begin();
    if (end == wordList.size()) return {};

    int begin =
        find(wordList.begin(), wordList.end(), beginWord) - wordList.begin();
    if (begin == wordList.size()) wordList.push_back(beginWord);

    int n = wordList.size();

    // Create Graph
    // Build two-dimensional matrix,
    // index : it's similar string;
    vector<vector<int>> g(n, vector<int>());
    for (int i = 0; i < wordList.size(); i++) {
      for (int j = i + 1; j < wordList.size(); j++) {
        if (similar(wordList[i], wordList[j])) {
          g[i].push_back(j);
          g[j].push_back(i);
        }
      }
    }

    // use bfs creat distance map
    // distance: every index related distance step
    // beginning from start point
    unordered_map<int, int> distance;
    bfs(g, begin, end, distance);

    // backtracking: according to distance, find minus path;
    vector<vector<string>> res;
    vector<int> tres = {begin};
    GetRes(g, begin, end, distance, wordList, tres, res);

    return res;
  }

 private:
  void bfs(const vector<vector<int>>& g, int begin, int end,
           unordered_map<int, int>& distance) {
    queue<int> q;
    q.push(begin);
    distance[begin] = 0;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      // assert(distance.find(cur) != distance.end());

      for (int j : g[cur]) {
        if (distance.find(j) == distance.end()) {
          distance[j] = distance[cur] + 1;
          q.push(j);
        }
      }
    }
  }

  void GetRes(vector<vector<int>>& g, int cur, int end,
              unordered_map<int, int>& distance, const vector<string>& wordList,
              vector<int>& tres, vector<vector<string>>& res) {
    if (tres.size() > 0 && tres[tres.size() - 1] == end) {
      res.push_back(GetPath(tres, wordList));
      return;
    }

    for (int i : g[cur]) {
      if (distance[i] == distance[cur] + 1) {
        tres.push_back(i);
        GetRes(g, i, end, distance, wordList, tres, res);
        tres.pop_back();
      }
    }

    return;
  }

  vector<string> GetPath(const vector<int>& path,
                         const vector<string>& wordList) {
    vector<string> ret;
    for (const int e : path) {
      ret.push_back(wordList[e]);
    }
    return ret;
  }

  bool similar(const string& word1, const string& word2) {
    // assert(word1 != "" && word1.size() == word2.size() && word1 != word2);

    int diff = 0;
    for (int i = 0; i < word1.size(); i++) {
      if (word1[i] != word2[i]) {
        diff++;
        if (diff > 1) return false;
      }
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Solution solu;
  string start("hit");
  string end("cog");
  vector<string> bank = {"hot", "dot", "dog", "lot", "log", "cog"};
  vector<vector<string>> ret = solu.findLadders(start, end, bank);
  return 0;
}
