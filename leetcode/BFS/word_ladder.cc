#include <cassert>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <queue>

#include "glog/logging.h"
#include "gflags/gflags.h"

using std::map;
using std::set;
using std::vector;
using std::queue;
using std::string;
using std::pair;
using std::unordered_set;
using std::find;

// Timeout
class Solution {
 public:
  int ladderLength(string start, string end, vector<string>& bank) {
    auto iter = find(bank.begin(), bank.end(), end);
    if (iter == bank.end()) return 0;
    set<string> uniq_bank(bank.begin(), bank.end());
    queue<pair<string, int>> try_step;
    try_step.push(make_pair(start, 1));
    auto iter_index = uniq_bank.find(start);
    if (iter_index != uniq_bank.end()) {
      uniq_bank.erase(iter_index);
    }
    // the char match replace chars
    string ralations = "abcdefghijklmnopqrstuvwxyz";
    while (!try_step.empty()) {
      // notice: please use front, not back, because it's bfs.
      pair<string,int> step = try_step.front();
      try_step.pop();
      if (step.first == end) return step.second;
      for (size_t i = 0; i < step.first.size(); ++i) {
        for (char item : ralations) {
          string new_step = step.first.substr(0,i);
          new_step.append(1, item);
          new_step += step.first.substr(i+1);
          auto index = find(uniq_bank.begin(), uniq_bank.end(), new_step);
          if (index != uniq_bank.end()) {
            try_step.push(make_pair(new_step, step.second+1));
            uniq_bank.erase(index);
          }
        }
      }
    }
    return 0;
  }
};


// Pass
class Solution1 {
 public:
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    unordered_set<string> word_set(wordList.begin(), wordList.end());

    // bfs
    queue<pair<string, int>> q;
    q.push(make_pair(beginWord, 1));
    if(word_set.find(beginWord) != word_set.end())
        word_set.erase(beginWord);

    vector<string> visited;

    while(!q.empty()){
      string cur_word = q.front().first;
      int cur_step = q.front().second;
      q.pop();

      visited.clear();
      for(string word: word_set) {
        if(similar(word, cur_word)) {
          if(word == endWord) return cur_step + 1;
          q.push(make_pair(word, cur_step + 1));
          visited.push_back(word);
        }
      }

      for(string word: visited) {
        word_set.erase(word);
      }
    }

    return 0;
  }

 private:
    bool similar(const string& word1, const string& word2) {

    assert(word1 != "" && word1.size() == word2.size() && word1 != word2);

    int diff = 0;
    for(int i = 0 ; i < word1.size() ; i ++) {
      if(word1[i] != word2[i]){
        diff ++;
        if(diff > 1) return false;
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
  vector<string> bank = {"hot","dot","dog","lot","log","cog"};
  int ret = solu.ladderLength(start, end, bank);
  LOG(INFO) << ret;
  Solution1 solu1;
  ret = solu1.ladderLength(start, end, bank);
  LOG(INFO) << ret;
  return 0;
}
