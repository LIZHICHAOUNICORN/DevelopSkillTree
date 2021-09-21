#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <algorithm>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

// Problem: https://leetcode-cn.com/problems/short-encoding-of-words/

using namespace std;

// trie
class Trie{
public:
    Trie*children[26];
    Trie() {
        memset(children, 0, sizeof(children));
    }
    void insert(string& word){
        Trie*root = this;
        for(int i=word.size()-1; i>=0; i--){
            char c = word[i];
            if(root->children[c-'a'] == nullptr)root->children[c-'a'] = new Trie();
            root = root->children[c-'a'];
        }
    }
    bool startWith(string& pre){
        Trie*root = this;
        for(char c:pre){
            if(root->children[c-'a'] == nullptr) return false;
            root = root->children[c-'a'];
        }
        return true;
    }
};

class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        struct {
            bool operator()(const string& a, const string& b) {
                return a.size() > b.size();
            }
        } customLess;

        std::sort(words.begin(), words.end(), customLess);
        int ans = 0;
        Trie root;
        for(auto& s:words){
            string rev(s);  
            reverse(rev.begin(),rev.end());
            if(root.startWith(rev)) continue;
            root.insert(s);
            ans += s.size()+1;
        }
        return ans;
    }
};

// 暴力
class Solution1 {
public:
    int minimumLengthEncoding(vector<string>& words) {
        unordered_set<string> good(words.begin(), words.end());
        for (const string& word: words) {
            for (int k = 1; k < word.size(); ++k) {
                good.erase(word.substr(k));
            }
        }

        int ans = 0;
        for (const string& word: good) {
            ans += word.size() + 1;
        }
        return ans;
    }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> wordDict({"time","me","bell"});

  Solution solu;
  auto ret = solu.minimumLengthEncoding(wordDict);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
