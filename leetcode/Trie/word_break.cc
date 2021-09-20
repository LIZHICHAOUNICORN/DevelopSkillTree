#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

// Problems: https://leetcode-cn.com/problems/word-break
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;

// build trie, and dfs search
class Solution {
    struct Node {
        unordered_map<char, int> node;
        bool isEnd = false;
    };
    vector<Node> trie;
    void TrieInsert(int tree_id, string& s, int pos) {
        if (pos == s.size()) {
            trie[tree_id].isEnd = true;
            return;
        }
        if (trie[tree_id].node.count(s[pos]) == 0) {
            trie[tree_id].node[s[pos]] = trie.size();
        }
        trie.push_back(Node());
        TrieInsert(trie[tree_id].node[s[pos]], s, pos+1);
    }

    void BuildTrie(string& s) {
        // 在第0层，从第0字符开始
        TrieInsert(0, s, 0);
    }

    bool dfs(string& s, int pos, vector<bool> visited) {
        if (visited[pos]) {
            return false;
        }
        int start = pos;
        auto trie_node = trie.begin();
        for (; start < s.size(); ++start) {
            // new start
            if (start > pos && trie_node->isEnd) {
                LOG(INFO) << "start: " << start << ", total size:"  << s.size() << ", dfs again";
                if (dfs(s, start, visited))
                return true;
            }
            if (trie_node->node.count(s[start]) == 0) {
                break;
            }
            // trie_id
            trie_node = trie.begin() + trie_node->node[s[start]];
        }
        if (start == s.size() && trie_node->isEnd) {
                return true;
        }
        visited[start] = true;
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // build trie
        trie.push_back(Node());
        for (auto& word : wordDict) {
            BuildTrie(word);
        }
        
        // dfs
        vector<bool> visited(s.size(), false);
        bool ret = dfs(s, 0, visited);
        return ret;
    }
};

// DP
class Solution1 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto wordDictSet = unordered_set <string> ();
        for (auto word: wordDict) {
            wordDictSet.insert(word);
        }

        auto dp = vector <bool> (s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.size()];
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  Solution solu;
  string s("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
           "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
           "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
  vector<string> wordDict({"a","aa","aaa","aaaa","aaaaa","aaaaaa",
                           "aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"});
  bool ret = solu.wordBreak(s, wordDict);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
