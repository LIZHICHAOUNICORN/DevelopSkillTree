#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

using namespace std;

// Problem: https://leetcode-cn.com/problems/design-twitter/

class Twitter {
 private:
  struct User {
    int user_id;
    vector<int> followed_ids;
    vector<pair<int, int>> posts;
    User(int user_id) { user_id = user_id; }
  };
  int time_count;       // 用于发Twitter 时间排序
  vector<User> users_;  // 用于快速索引用户;
  unordered_map<int, int>
      user_ids;  // 根据用户id,及用户id在users_ 位置建立索引。

 public:
  /** Initialize your data structure here. */
  Twitter() {
    time_count = 1;
    users_.clear();
    user_ids.clear();
  }

  /** Compose a new tweet. */
  void postTweet(int userId, int tweetId) {
    // 判断用户是否已经在索引中
    if (!user_ids.count(userId)) {
      users_.push_back(User(userId));
      user_ids[userId] = users_.size() - 1;
    }
    int index = user_ids[userId];
    // 将用户推文加入队列，注意要有时间信息
    users_[index].posts.push_back(make_pair(tweetId, time_count++));
  }

  /** Retrieve the 10 most recent tweet ids in the
      user's news feed. Each item in the news feed
      must be posted by users who the user followed
      or by the user herself. Tweets must be ordered
      from most recent to least recent. */
  vector<int> getNewsFeed(int userId) {
    // shabi
    if (!user_ids.count(userId)) {
      users_.emplace_back(User(userId));
      user_ids[userId] = users_.size() - 1;
    }
    // 使用优先队列，根据时间信息进行排序
    int index = user_ids[userId];
    auto cmp = [](const pair<int, int>& left, const pair<int, int>& right) {
      return left.second < right.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> feeds(
        cmp);
    // user
    for (pair<int, int>& post : users_[index].posts) {
      feeds.push(post);
    }

    // followed
    vector<int>& followed_ids = users_[index].followed_ids;
    for (int& user_id : followed_ids) {
      int id_index = user_ids[user_id];
      for (pair<int, int>& post : users_[id_index].posts) {
        feeds.push(post);
      }
    }

    vector<int> ret;
    while (!feeds.empty()) {
      ret.push_back(feeds.top().first);
      feeds.pop();
      // 注意只取前十
      if (ret.size() == 10) break;
    }
    return ret;
  }

  /** Follower follows a followee. If the operation is invalid, it should be a
   * no-op. */
  void follow(int followerId, int followeeId) {
    if (!user_ids.count(followerId)) {
      users_.emplace_back(User(followerId));
      user_ids[followerId] = users_.size() - 1;
    }
    int index = user_ids[followerId];
    auto it = find(users_[index].followed_ids.begin(),
                   users_[index].followed_ids.end(), followeeId);
    if (it == users_[index].followed_ids.end()) {
      users_[index].followed_ids.push_back(followeeId);
    }

    if (!user_ids.count(followeeId)) {
      users_.emplace_back(User(followeeId));
      user_ids[followeeId] = users_.size() - 1;
    }
  }

  /** Follower unfollows a followee. If the operation is invalid, it should be a
   * no-op. */
  void unfollow(int followerId, int followeeId) {
    int index = user_ids[followerId];
    vector<int>& flolowed_ids = users_[index].followed_ids;
    vector<int>::iterator it = flolowed_ids.begin();
    for (; it != flolowed_ids.end(); ++it) {
      if (*it == followeeId) break;
    }
    // not fount followeeId.
    if (it == flolowed_ids.end()) return;
    flolowed_ids.erase(it);
  }
};

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  Twitter tw;
  tw.postTweet(1, 5);
  tw.postTweet(1, 3);
  tw.getNewsFeed(1);

  return 0;
}
