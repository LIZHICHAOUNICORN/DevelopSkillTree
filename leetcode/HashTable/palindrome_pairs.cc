#include <algorithm>
#include <unordered_map>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/palindrome-pairs/

using namespace std;

// Trie
class Solution {
 public:
  struct node {
    int ch[26];
    int flag;
    node() {
      flag = -1;
      memset(ch, 0, sizeof(ch));
    }
  };

  vector<node> tree;

  void insert(string& s, int id) {
    int len = s.length(), add = 0;
    for (int i = 0; i < len; i++) {
      int x = s[i] - 'a';
      if (!tree[add].ch[x]) {
        tree.emplace_back();
        tree[add].ch[x] = tree.size() - 1;
      }
      add = tree[add].ch[x];
    }
    tree[add].flag = id;
  }

  int findWord(string& s, int left, int right) {
    int add = 0;
    for (int i = right; i >= left; i--) {
      int x = s[i] - 'a';
      if (!tree[add].ch[x]) {
        return -1;
      }
      add = tree[add].ch[x];
    }
    return tree[add].flag;
  }

  bool isPalindrome(string& s, int left, int right) {
    int len = right - left + 1;
    for (int i = 0; i < len / 2; i++) {
      if (s[left + i] != s[right - i]) {
        return false;
      }
    }
    return true;
  }

  vector<vector<int>> palindromePairs(vector<string>& words) {
    tree.emplace_back(node());
    int n = words.size();
    for (int i = 0; i < n; i++) {
      insert(words[i], i);
    }
    vector<vector<int>> ret;
    for (int i = 0; i < n; i++) {
      int m = words[i].size();
      for (int j = 0; j <= m; j++) {
        if (isPalindrome(words[i], j, m - 1)) {
          int left_id = findWord(words[i], 0, j - 1);
          if (left_id != -1 && left_id != i) {
            ret.push_back({i, left_id});
          }
        }
        if (j && isPalindrome(words[i], 0, j - 1)) {
          int right_id = findWord(words[i], j, m - 1);
          if (right_id != -1 && right_id != i) {
            ret.push_back({right_id, i});
          }
        }
      }
    }
    return ret;
  }
};

// Hashtable
class Solution1 {
 private:
  vector<string> wordsRev;
  unordered_map<string_view, int> indices;

 public:
  int findWord(const string_view& s, int left, int right) {
    auto iter = indices.find(s.substr(left, right - left + 1));
    return iter == indices.end() ? -1 : iter->second;
  }

  bool isPalindrome(const string_view& s, int left, int right) {
    int len = right - left + 1;
    for (int i = 0; i < len / 2; i++) {
      if (s[left + i] != s[right - i]) {
        return false;
      }
    }
    return true;
  }

  vector<vector<int>> palindromePairs(vector<string>& words) {
    int n = words.size();
    for (const string& word : words) {
      wordsRev.push_back(word);
      reverse(wordsRev.back().begin(), wordsRev.back().end());
    }
    for (int i = 0; i < n; ++i) {
      indices.emplace(wordsRev[i], i);
    }

    vector<vector<int>> ret;
    for (int i = 0; i < n; i++) {
      int m = words[i].size();
      if (!m) {
        continue;
      }
      string_view wordView(words[i]);
      for (int j = 0; j <= m; j++) {
        if (isPalindrome(wordView, j, m - 1)) {
          int left_id = findWord(wordView, 0, j - 1);
          if (left_id != -1 && left_id != i) {
            ret.push_back({i, left_id});
          }
        }
        if (j && isPalindrome(wordView, 0, j - 1)) {
          int right_id = findWord(wordView, j, m - 1);
          if (right_id != -1 && right_id != i) {
            ret.push_back({right_id, i});
          }
        }
      }
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> words({"abcd", "dcba", "lls", "s", "sssll"});

  Solution solu;
  auto ret = solu.palindromePairs(words);
  LOG(INFO) << ret.back().back();
  return 0;
}
