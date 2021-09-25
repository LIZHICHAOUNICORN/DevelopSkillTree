## Trie

### 实现
一种是递归方式

```

class Trie {
 private:
  struct Node {
    map<char, int> next;
    bool end = false;
  };
  vector<Node> trie;

 public:
  Trie() {
    trie.clear();
    trie.push_back(Node());
  }

  /** Inserts a word into the trie. */
  void insert(const string& word) { insert(0, word, 0); }

  /** Returns if the word is in the trie. */
  bool search(const string& word) { return search(0, word, 0); }

  /** Returns if there is any word in the trie that starts with the given
   * prefix. */
  bool startsWith(const string& prefix) { return startsWith(0, prefix, 0); }

 private:
  void insert(int treeID, const string& word, int index) {
    if (index == word.size()) {
      trie[treeID].end = true;
      return;
    }

    if (trie[treeID].next.find(word[index]) == trie[treeID].next.end()) {
      trie[treeID].next[word[index]] = trie.size();
      trie.push_back(Node());
    }

    insert(trie[treeID].next[word[index]], word, index + 1);
  }

  bool search(int treeID, const string& word, int index) {
    if (index == word.size()) return trie[treeID].end;

    if (trie[treeID].next.find(word[index]) == trie[treeID].next.end())
      return false;

    return search(trie[treeID].next[word[index]], word, index + 1);
  }

  bool startsWith(int treeID, const string& prefix, int index) {
    if (index == prefix.size()) return true;

    if (trie[treeID].next.find(prefix[index]) == trie[treeID].next.end())
      return false;

    return startsWith(trie[treeID].next[prefix[index]], prefix, index + 1);
  }
};

```
迭代方式


### 性质

### 应用场景

### leetcode 题目
