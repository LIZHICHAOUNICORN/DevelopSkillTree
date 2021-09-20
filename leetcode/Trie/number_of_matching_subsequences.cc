#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

// Problem: https://leetcode-cn.com/problems/map-sum-pairs/

using namespace std;

class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        vector<queue<pair<int, int>>> buckets(26);
        for(int i = 0; i < words.size(); i++){
            buckets[words[i][0]-'a'].push({i, 0});
        }
        int res = 0;
        for(auto c: S){
            queue<pair<int, int>> & q = buckets[c-'a'];
            for(int i = q.size(); i > 0; i--){
                auto [wordIndex, posIndex] = q.front();
                q.pop();
                posIndex++;
                if(posIndex == words[wordIndex].length()){
                    res++;
                }
                else{
                    buckets[words[wordIndex][posIndex] - 'a'].push({wordIndex, posIndex});
                }
            }
        }
        return res;
    }
};

class Solution1 {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int ret = 0;
        for (auto& word : words) {
            int i = 0;
            int pos = -1;
            for (i = 0; i < s.size(); ++i) {
                pos = s.find_first_of(word[i], pos + 1);
                if (pos == -1) break;
            }
            if (i == word.size()) ret += 1;
        }
        return ret;

    }
};

class Solution2 {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int ret = 0;
        for (auto& word : words) {
            int k = 0;
            for (int i = 0; i < s.size() && k < word.size(); ++i) {
                if(word[k] == s[i]) {
                    ++k;
                }
            }
            if (k == word.size()) ret += 1;
        }
        return ret;

    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  string s("abcde");
  vector<string> wordDict({"a","bb","acd","ace"});

  Solution solu;
  int ret = solu.numMatchingSubseq(wordDict, s);
  LOG(INFO) << "ret: " << ret;
  return 0;
}
