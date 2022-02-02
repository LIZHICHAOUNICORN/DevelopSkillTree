#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

DEFINE_int32(max_value, 100, "the max value of range");

static long long sum;

void serial_worker(int start, int end) {
  int local_sum = 0;
  for (int i = start; i <= end; ++i) {
    local_sum += std::sqrt(i);
  }
  VLOG(1) << "start: " << start << ", end: " << end << ", sum: " << local_sum;
  sum += local_sum;
}

void serial_task(int start, int end) {
  auto start_time = std::chrono::high_resolution_clock::now();
  sum = 0;
  serial_worker(start, end);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto time_consume = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  LOG(INFO) << "sum: " << sum << ", time consume: " << time_consume.count();
}

void worker(int start, int end, std::mutex* con_mutex) {
  int local_sum = 0;
  for (int i = start + 1; i <= end; ++i) {
    local_sum += std::sqrt(i);
  }

  {
    std::lock_guard<std::mutex> lock(*con_mutex);
    sum += local_sum;
    VLOG(1) << std::this_thread::get_id() << ", start: " << start
            << ", end: " << end << ", sum: " << sum;
  }
}

void concurrent_task(int start, int end) {
  auto start_time = std::chrono::high_resolution_clock::now();
  int s = start;
  sum = 0;
  std::vector<std::thread> threads;
  std::mutex con_mutex;

  unsigned concurrent_count = std::thread::hardware_concurrency();
  LOG(INFO) << "concurrent worker: " << concurrent_count;

  int part = end / concurrent_count;
  for (int i = 0; i < concurrent_count; ++i) {
    int e = part * (i + 1);
    if (i == concurrent_count - 1) e = end;
    threads.push_back(std::thread(worker, s, e, &con_mutex));
    s = e;
  }

  for (auto it = threads.begin(); it != threads.end(); ++it) {
    it->join();
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto time_consume = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  LOG(INFO) << "sum: " << sum
            << ", concurrent task time: " << time_consume.count();
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  serial_task(0, FLAGS_max_value);
  concurrent_task(0, FLAGS_max_value);

  return 0;
}
