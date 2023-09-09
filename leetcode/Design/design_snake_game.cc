#include <algorithm>
#include <functional>
#include <queue>
#include <deque>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// Problem: https://leetcode-cn.com/problems/lru-cache/
class SnakeGame {
 public:
  /** Initialize your data structure here.
      @param width - screen width
      @param height - screen height
      @param food - A list of food positions
      E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the
     second is at [1,0]. */
  SnakeGame(int width, int height, vector<vector<int>>& food) {
    this->width = width;
    this->height = height;
    this->food = food;
    dq.push_back(make_pair(0, 0));
    end = false;
    index = 0;
  }

  /** Moves the snake.
      @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
      @return The game's score after the move. Return -1 if game over.
      Game over when snake crosses the screen boundary or bites its body. */
  int move(string direction) {
    // 如果之前有吃到自己或者撞到墙壁，那么就直接返回-1
    if (end) return -1;
    // 取出头部位置并按照要求去进行变化
    pair<int, int> cur = dq.front();
    if (direction == "U")
      cur.first--;
    else if (direction == "D")
      cur.first++;
    else if (direction == "L")
      cur.second--;
    else if (direction == "R")
      cur.second++;
    // 如果撞墙
    if (cur.first < 0 || cur.first >= height || cur.second < 0 ||
        cur.second >= width) {
      end = true;
      return -1;
    }
    // 如果吃到自己,注意尾部最后一个节点不算
    for (auto iter = dq.begin(); iter != dq.end() - 1; iter++) {
      if ((*iter).first == cur.first && (*iter).second == cur.second) {
        end = true;
        return -1;
      }
    }
    // 如果没有食物了,就直接返回,记得蛇位置也要移动一下
    if (index == food.size()) {
      dq.push_front(cur);
      dq.pop_back();
      return index;
    }
    // 头部插入新的位置
    dq.push_front(cur);
    // 如果吃到食物,身体就增长1个,增长的就是尾部位置
    if (cur.first == food[index][0] && cur.second == food[index][1]) {
      index++;
    }
    // 如果没有吃到食物,最后一个位置更新一下
    else {
      dq.pop_back();
    }
    return index;
  }

 private:
  deque<pair<int, int>> dq;
  int width, height;
  vector<vector<int>> food;
  bool end;
  int index;
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);


  return 0;
}
