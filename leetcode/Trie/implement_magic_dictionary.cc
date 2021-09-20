#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>

#include "third_party/glog/include/logging.h"
#include "third_party/gflags/include/gflags.h"

// Problem: https://leetcode-cn.com/problems/implement-magic-dictionary/
// Solutions: https://leetcode-cn.com/problems/implement-magic-dictionary/solution/zi-dian-shu-c-bao-li-26zi-mu-by-zhouziho-ovd9/

using namespace std;

class Trie{
public:
    Trie*children[26];
    bool isEnd;
    Trie(){
        memset(children,0,sizeof(children));
        isEnd=false;
    }
    void insert(string&word){
        Trie*root=this;
        for(char c:word){
            if(root->children[c-'a']==nullptr)root->children[c-'a']=new Trie();
            root=root->children[c-'a'];
        }
        root->isEnd=true;
    }
    bool search(string&word){
        Trie*root=this;
        for(char c:word){
            if(root->children[c-'a']==nullptr)return false;
            root=root->children[c-'a'];
        }
        return root->isEnd;
    }
};

class MagicDictionary {
public:
    Trie*root;
    MagicDictionary() {
        root=new Trie();
    }
    
    void buildDict(vector<string> dictionary) {
        for(string s:dictionary){
            root->insert(s);
        }
    }
    
    bool search(string searchWord) {
        for(int i=0; i<searchWord.size(); i++){
            char tmp = searchWord[i];
            for(char c='a'; c<='z'; c++){
                if(c == tmp) continue;
                searchWord[i]=c;
                //cout<<searchWord<<endl;
                if(root->search(searchWord))return true;
            }
            searchWord[i]=tmp;
        }
        return false;
    }
};


int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  vector<string> wordDict({"hello","leetcode"});

  MagicDictionary magic;
  magic.buildDict(wordDict);
  bool ret = magic.search("hello");
  ret = magic.search("hell");
  ret = magic.search("hhllo");
  LOG(INFO) << "ret: " << ret;
  return 0;
}
