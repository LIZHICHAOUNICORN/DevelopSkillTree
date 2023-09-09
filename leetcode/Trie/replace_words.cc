#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

// Problem: https://leetcode-cn.com/problems/replace-words/
// Solutions:
// https://leetcode-cn.com/problems/replace-words/solution/c-chao-guo-96-qian-zhui-shu-de-qing-xi-j-3ld7/

using namespace std;

class Solution {
 public:
  struct TrieNode {
    string word;
    TrieNode* children[26];

    // 初始化
    TrieNode() {
      word = "";

      // 利用memset方法，把children所有元素填充0
      memset(children, 0, sizeof(children));
    }
  };

  vector<string> Split(string& str) {
    vector<string> res;

    // 转化成为stringsteam对象
    stringstream ss(str);

    string curr;

    // 使用std::getline方法按照空格分割
    // stringstream对象ss，并把结果存储到curr当中
    while (std::getline(ss, curr, ' ')) {
      if (curr.size() > 0) {
        res.push_back(curr);
      }
    }
    return res;
  }

  string replaceWords(vector<string>& dictionary, string sentence) {
    TrieNode* root = new TrieNode();
    for (int i = 0; i < dictionary.size(); i++) {
      TrieNode* curr = root;
      for (char letter : dictionary[i]) {
        if (curr->children[letter - 'a'] == NULL) {
          curr->children[letter - 'a'] = new TrieNode();
        }  //不断往下插入字母
        curr = curr->children[letter - 'a'];
      }
      //直到最后插入一个前缀的所有字母之后，在最后一个节点存储前缀单词名称
      curr->word = dictionary[i];
    }

    //首先利用之前实现的split方法，分割字符串
    vector<string> words = Split(sentence);
    string res;

    for (int i = 0; i < words.size(); i++) {
      TrieNode* curr = root;
      for (char letter : words[i]) {
        // 如果没有对应的子节点了，就跳出对words[i]的循环，不对它进行替换
        if (curr->children[letter - 'a'] == NULL) {
          break;
        } else {
          curr = curr->children[letter - 'a'];

          // 如果当前节点的前缀不为空了，
          // 意味着到达了最短的前缀，此时完成替换过程，跳出当前的循环
          if (!curr->word.empty()) {
            break;
          }
        }
      }
      // 除了刚开始，其他的时候在插入字符串之前，都要先插入“ ”
      if (!res.empty()) {
        res += " ";
      }
      // 如果当前的前缀是空，则说明是没有合适替换的情况，
      // 此时不进行替换，直接插入原单词，反之，如果为空，则进行最短前缀的替换
      res += (curr->word.empty()) ? words[i] : curr->word;
    }
    return res;
  }
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
