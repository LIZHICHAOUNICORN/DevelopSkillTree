#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problems:
// https://leetcode-cn.com/problems/design-add-and-search-words-data-structure/

using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;

class WordDictionary {
  struct Node {
    unordered_map<char, int> next;
    bool isEnd;
  };
  vector<Node> trie;
  void InsertTrie(int tree_id, string& word, int pos) {
    if (pos == word.size()) {
      trie[tree_id].isEnd = true;
      return;
    }
    if (trie[tree_id].next.find(word[pos]) == trie[tree_id].next.end()) {
      trie[tree_id].next[word[pos]] = trie.size();
      trie.push_back(Node());
    }
    InsertTrie(trie[tree_id].next[word[pos]], word, pos + 1);
  }
  bool SearchTrie(int tree_id, string& word, int pos) {
    if (pos == word.size()) {
      return trie[tree_id].isEnd;
    }
    if (trie[tree_id].next.find(word[pos]) == trie[tree_id].next.end()) {
      // 通配符
      if (word[pos] == '.') {
        // for (auto& [key, value] : trie[tree_id].next) {
        for (auto item : trie[tree_id].next) {
          if (SearchTrie(item.second, word, pos + 1)) {
            return true;
          }
        }
      }
      return false;
    }
    return SearchTrie(trie[tree_id].next[word[pos]], word, pos + 1);
  }

 public:
  /** Initialize your data structure here. */
  WordDictionary() { trie.push_back(Node()); }

  void addWord(string word) { InsertTrie(0, word, 0); }

  bool search(string word) { return SearchTrie(0, word, 0); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  WordDictionary solu;
  solu.addWord("bad");
  bool ret = solu.search("bad");
  LOG(INFO) << ret;
  return 0;
}
