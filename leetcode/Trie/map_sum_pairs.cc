#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem: https://leetcode-cn.com/problems/map-sum-pairs/

using namespace std;

class Trie {
 public:
  vector<Trie*> children;
  bool isEnd;
  int val;
  Trie() {
    isEnd = false;
    children.resize(26, 0);
  }
  void insert(string& word, int val) {
    Trie* root = this;
    for (char c : word) {
      if (root->children[c - 'a'] == nullptr)
        root->children[c - 'a'] = new Trie();
      root = root->children[c - 'a'];
    }
    root->isEnd = true;
    root->val = val;
  }
  int searchAndGet(string& pre) {
    Trie* root = this;
    for (char c : pre) {
      if (root->children[c - 'a'] == nullptr) return 0;
      root = root->children[c - 'a'];
    }
    return dfs(root);
  }
  int dfs(Trie* root) {
    int ans = 0;
    if (root->isEnd) ans += root->val;
    for (auto child : root->children) {
      if (child == nullptr) continue;
      ans += dfs(child);
    }
    return ans;
  }
};
class MapSum {
 public:
  Trie* root;
  MapSum() { root = new Trie(); }

  void insert(string key, int val) { root->insert(key, val); }

  int sum(string prefix) { return root->searchAndGet(prefix); }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string s("the cattle was rattled by the battery");
  vector<string> wordDict({"cat", "bat", "rat"});

  Solution solu;
  string ret = solu.replaceWords(wordDict, s);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
