#include <algorithm>
#include <functional>
#include <list>
#include <set>
#include <unordered_map>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/lfu-cache/

struct Node {
  int cnt, time, key, value;

  Node(int _cnt, int _time, int _key, int _value)
      : cnt(_cnt), time(_time), key(_key), value(_value) {}

  bool operator<(const Node& rhs) const {
    return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
  }
};
class LFUCache {
  // 缓存容量，时间戳
  int capacity, time;
  unordered_map<int, Node> key_table;
  set<Node> S;

 public:
  LFUCache(int _capacity) {
    capacity = _capacity;
    time = 0;
    key_table.clear();
    S.clear();
  }

  int get(int key) {
    if (capacity == 0) return -1;
    auto it = key_table.find(key);
    // 如果哈希表中没有键 key，返回 -1
    if (it == key_table.end()) return -1;
    // 从哈希表中得到旧的缓存
    Node cache = it->second;
    // 从平衡二叉树中删除旧的缓存
    S.erase(cache);
    // 将旧缓存更新
    cache.cnt += 1;
    cache.time = ++time;
    // 将新缓存重新放入哈希表和平衡二叉树中
    S.insert(cache);
    it->second = cache;
    return cache.value;
  }

  void put(int key, int value) {
    if (capacity == 0) return;
    auto it = key_table.find(key);
    if (it == key_table.end()) {
      // 如果到达缓存容量上限
      if (key_table.size() == capacity) {
        // 从哈希表和平衡二叉树中删除最近最少使用的缓存
        key_table.erase(S.begin()->key);
        S.erase(S.begin());
      }
      // 创建新的缓存
      Node cache = Node(1, ++time, key, value);
      // 将新缓存放入哈希表和平衡二叉树中
      key_table.insert(make_pair(key, cache));
      S.insert(cache);
    } else {
      // 这里和 get() 函数类似
      Node cache = it->second;
      S.erase(cache);
      cache.cnt += 1;
      cache.time = ++time;
      cache.value = value;
      S.insert(cache);
      it->second = cache;
    }
  }
};

struct LinkedNode {
  int key, val, freq;
  LinkedNode(int _key, int _val, int _freq) : key(_key), val(_val), freq(_freq) {}
};
class LFUCache1 {
  int minfreq, capacity;
  unordered_map<int, list<LinkedNode>::iterator> key_table;
  unordered_map<int, list<LinkedNode>> freq_table;

 public:
  LFUCache1(int _capacity) {
    minfreq = 0;
    capacity = _capacity;
    key_table.clear();
    freq_table.clear();
  }

  int get(int key) {
    if (capacity == 0) return -1;
    auto it = key_table.find(key);
    if (it == key_table.end()) return -1;
    list<LinkedNode>::iterator node = it->second;
    int val = node->val, freq = node->freq;
    freq_table[freq].erase(node);
    // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
    if (freq_table[freq].size() == 0) {
      freq_table.erase(freq);
      if (minfreq == freq) minfreq += 1;
    }
    // 插入到 freq + 1 中
    freq_table[freq + 1].push_front(LinkedNode(key, val, freq + 1));
    key_table[key] = freq_table[freq + 1].begin();
    return val;
  }

  void put(int key, int value) {
    if (capacity == 0) return;
    auto it = key_table.find(key);
    if (it == key_table.end()) {
      // 缓存已满，需要进行删除操作
      if (key_table.size() == capacity) {
        // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
        auto it2 = freq_table[minfreq].back();
        key_table.erase(it2.key);
        freq_table[minfreq].pop_back();
        if (freq_table[minfreq].size() == 0) {
          freq_table.erase(minfreq);
        }
      }
      freq_table[1].push_front(LinkedNode(key, value, 1));
      key_table[key] = freq_table[1].begin();
      minfreq = 1;
    } else {
      // 与 get 操作基本一致，除了需要更新缓存的值
      list<LinkedNode>::iterator node = it->second;
      int freq = node->freq;
      freq_table[freq].erase(node);
      if (freq_table[freq].size() == 0) {
        freq_table.erase(freq);
        if (minfreq == freq) minfreq += 1;
      }
      freq_table[freq + 1].push_front(LinkedNode(key, value, freq + 1));
      key_table[key] = freq_table[freq + 1].begin();
    }
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  LFUCache lfu(3);
  lfu.put(1, 2);
  lfu.put(1, 3);
  lfu.put(4, 3);
  lfu.put(5, 3);
  LOG(INFO) << lfu.get(4);

  return 0;
}
