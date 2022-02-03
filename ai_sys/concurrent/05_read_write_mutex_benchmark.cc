#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

//读线程数量
#define READER_THREAD_COUNT 8
//最大循环次数
#define LOOP_COUNT 5000000

class SharedMutexCounter {
 public:
  SharedMutexCounter() : value_(0) {}

  // Multiple threads/readers can read the counter's value at the same time.
  std::size_t Get() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return value_;
  }

  // Only one thread/writer can increment/write the counter's value.
  void Increase() {
    // You can also use lock_guard here.
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_++;
  }

  // Only one thread/writer can reset/write the counter's value.
  void Reset() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_ = 0;
  }

 private:
  mutable std::shared_mutex mutex_;
  std::size_t value_;
};

class MutexCounter {
 public:
  MutexCounter() : value_(0) {}

  // Multiple threads/readers can read the counter's value at the same time.
  std::size_t Get() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return value_;
  }

  // Only one thread/writer can increment/write the counter's value.
  void Increase() {
    // You can also use lock_guard here.
    std::lock_guard<std::mutex> lock(mutex_);
    value_++;
  }

  // Only one thread/writer can reset/write the counter's value.
  void Reset() {
    std::lock_guard<std::mutex> lock(mutex_);
    value_ = 0;
  }

 private:
  mutable std::mutex mutex_;
  std::size_t value_;
};

void test_shared_mutex() {
  SharedMutexCounter counter;
  int temp;

  //写线程函数
  auto writer = [&counter]() {
    for (int i = 0; i < LOOP_COUNT; i++) {
      counter.Increase();
    }
  };

  //读线程函数
  auto reader = [&counter, &temp]() {
    for (int i = 0; i < LOOP_COUNT; i++) {
      temp = counter.Get();
    }
  };

  //存放读线程对象指针的数组
  std::thread** tarray = new std::thread*[READER_THREAD_COUNT];

  //记录起始时间
  clock_t start = clock();

  //创建READER_THREAD_COUNT个读线程
  for (int i = 0; i < READER_THREAD_COUNT; i++) {
    tarray[i] = new std::thread(reader);
  }

  //创建一个写线程
  std::thread tw(writer);

  for (int i = 0; i < READER_THREAD_COUNT; i++) {
    tarray[i]->join();
  }
  tw.join();

  //记录起始时间
  clock_t end = clock();
  printf("[test_shared_mutex]\n");
  printf("thread count: %d\n", READER_THREAD_COUNT);
  printf("result: %d cost: %dms temp: %d \n", counter.Get(), end - start, temp);
}

//测试std::mutex
void test_mutex() {
  MutexCounter counter;

  int temp;

  //写线程函数
  auto writer = [&counter]() {
    for (int i = 0; i < LOOP_COUNT; i++) {
      counter.Increase();
    }
  };

  //读线程函数
  auto reader = [&counter, &temp]() {
    for (int i = 0; i < LOOP_COUNT; i++) {
      temp = counter.Get();
    }
  };

  //存放读线程对象指针的数组
  std::thread** tarray = new std::thread*[READER_THREAD_COUNT];

  //记录起始时间
  clock_t start = clock();

  //创建READER_THREAD_COUNT个读线程
  for (int i = 0; i < READER_THREAD_COUNT; i++) {
    tarray[i] = new std::thread(reader);
  }

  //创建一个写线程
  std::thread tw(writer);

  for (int i = 0; i < READER_THREAD_COUNT; i++) {
    tarray[i]->join();
  }
  tw.join();

  //记录结束时间
  clock_t end = clock();
  printf("[test_mutex]\n");
  printf("thread count:%d\n", READER_THREAD_COUNT);
  printf("result:%d cost:%dms temp:%d \n", counter.Get(), end - start, temp);
}

int main() {
  // test_mutex();
  test_shared_mutex();
  return 0;
}
