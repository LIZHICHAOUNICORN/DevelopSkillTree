#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/search-suggestions-system/
// Solutions:
// https://leetcode-cn.com/problems/implement-magic-dictionary/solution/zi-dian-shu-c-bao-li-26zi-mu-by-zhouziho-ovd9/

using namespace std;

struct Trie {
  unordered_map<char, shared_ptr<Trie>> child;
  priority_queue<string> words;
};

class Solution {
 private:
  void addWord(shared_ptr<Trie> root, const string& word) {
    shared_ptr<Trie> cur(root);
    for (const char& ch : word) {
      if (!cur->child.count(ch)) {
        cur->child[ch].reset(new Trie());
      }
      cur = cur->child[ch];
      cur->words.push(word);
      if (cur->words.size() > 3) {
        cur->words.pop();
      }
    }
  }

 public:
  vector<vector<string>> suggestedProducts(vector<string>& products,
                                           string searchWord) {
    shared_ptr<Trie> root(new Trie());
    for (const string& word : products) {
      addWord(root, word);
    }

    vector<vector<string>> ans;
    shared_ptr<Trie> cur = root;
    bool flag = false;
    for (const char& ch : searchWord) {
      if (flag || !cur->child.count(ch)) {
        ans.emplace_back();
        flag = true;
      } else {
        cur = cur->child[ch];
        vector<string> selects;
        while (!cur->words.empty()) {
          selects.push_back(cur->words.top());
          cur->words.pop();
        }
        reverse(selects.begin(), selects.end());
        ans.push_back(move(selects));
      }
    }

    return ans;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> products(
      {"mobile", "mouse", "moneypot", "monitor", "mousepad"});
  string search_word("mouse");
  Solution solu;
  auto ret = solu.suggestedProducts(products, search_word);

  return 0;
}
