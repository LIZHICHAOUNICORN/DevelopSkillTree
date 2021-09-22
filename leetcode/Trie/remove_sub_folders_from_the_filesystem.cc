#include <map>
#include <string>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// Problem:
// https://leetcode-cn.com/problems/remove-sub-folders-from-the-filesystem/
// Solutions:
// https://leetcode-cn.com/problems/remove-sub-folders-from-the-filesystem/solution/shi-yong-trie-dui-qian-zhui-bian-li-cha-1nb79/

using namespace std;

class Solution {
 private:
  class Trie {
    struct TrieNode {
      map<char, int> next;
      bool isEnd;
    };

    vector<TrieNode> trie;

   public:
    Trie() { trie.push_back(TrieNode()); }
    void Insert(int tree_id, string& word, int pos) {
      if (pos == word.size()) {
        trie[tree_id].isEnd = true;
        return;
      }
      if (trie[tree_id].next.count(word[pos]) == 0) {
        trie[tree_id].next[word[pos]] = trie.size();
        trie.push_back(TrieNode());
      }
      Insert(trie[tree_id].next[word[pos]], word, pos + 1);
    }
    bool Search(int tree_id, string& word, int pos) {
      if (pos == word.size()) {
        return trie[tree_id].isEnd;
      }
      if (trie[tree_id].next.count(word[pos]) == 0) {
        return false;
      }
      return Search(trie[tree_id].next[word[pos]], word, pos + 1);
    }

    bool StartWith(int tree_id, string& word, int pos) {
      if (pos == word.size()) return true;
      if (trie[tree_id].next.count(word[pos]) == 0) {
        return false;
      }
      return StartWith(trie[tree_id].next[word[pos]], word, pos + 1);
    }
  };

 public:
  vector<string> removeSubfolders(vector<string>& folder) {
    // 例如：["/c/d","/c/d/e","/c/f"]，依次插入folder 建立trie.
    Trie t;
    for (auto& path : folder) {
      t.Insert(0, path, 0);
    }

    vector<string> ret;
    // 对所有路径进行遍历。
    for (auto& path : folder) {
      // 取每个路径的子路径查询，例如 ["/c/d","/c/d/e","/c/f"]
      // 对 path="/c/d/e" 进行依次查询："/c/d",
      // "/c"，如果存在("/c/d")，那么path是子路径
      // 否则 它不是子路径。
      int start = 0;
      int last_pos = path.size();
      bool found = false;
      while (last_pos > 0) {
        last_pos = path.substr(start, last_pos).find_last_of('/');
        // 找不到就跳出
        if (last_pos == std::string::npos) break;
        string sub_str = path.substr(0, last_pos);
        if (t.Search(0, sub_str, 0)) {
          found = true;
          break;
        }
      }
      if (!found) ret.push_back(path);
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> wordDict({"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"});

  Solution solu;
  auto ret = solu.removeSubfolders(wordDict);
  return 0;
}
