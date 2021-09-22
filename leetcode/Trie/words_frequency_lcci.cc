#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/words-frequency-lcci/

using namespace std;

struct TiredNode {
  int freq;
  shared_ptr<TiredNode> children[26];
  TiredNode(int freq) {
    this->freq = freq;
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
  }
};

class TiredTree {
 private:
  shared_ptr<TiredNode> root;

 public:
  TiredTree() { root = make_shared<TiredNode>(0); }

  void add(const std::string word) {
    size_t size = word.size();
    shared_ptr<TiredNode> cur = root;
    for (int i = 0; i < size; i++) {
      int pos = word[i] - 'a';
      if (cur->children[pos] == nullptr) {
        cur->children[pos] = make_shared<TiredNode>(0);
      }
      cur = cur->children[pos];
    }
    cur->freq++;
  }

  int search(const std::string word) {
    size_t size = word.size();
    shared_ptr<TiredNode> cur = root;
    for (int i = 0; i < size; i++) {
      int pos = word[i] - 'a';
      if (cur->children[pos] == nullptr) return 0;
      cur = cur->children[pos];
    }
    return cur->freq;
  }
};

// Trie
class WordsFrequency {
 public:
  WordsFrequency(vector<string>& book) {
    size_t size = book.size();
    for (int i = 0; i < size; i++) {
      tree.add(book[i]);
    }
  }

  int get(string word) { return tree.search(word); }

 private:
  TiredTree tree;
};

// Hashtable
class WordsFrequency1 {
 public:
  WordsFrequency(vector<string>& book) {
    size_t size = book.size();
    for (int i = 0; i < size; i++) {
      hash[book[i]]++;
    }
  }

  int get(string word) {
    if (hash.count(word)) return hash[word];
    return 0;
  }

 private:
  unordered_map<string, int> hash;
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
