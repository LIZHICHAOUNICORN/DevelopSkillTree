#include <bitset>
#include <iostream>

#include "third_party/gflags/include/gflags.h"
#include "third_party/glog/include/logging.h"

// #define UINT64_C(v)  (v ## ULL)

using namespace std;

void bitmap_locate(uint64_t word, uint16_t pos) {
  int num_index = pos >> 6;
  const int index = pos & 63;
  const uint64_t new_word = word | (UINT64_C(1) << index);
  int cardinality = (uint32_t)((word ^ new_word) >> index);
  LOG(INFO) << "world: " << std::bitset<64>(word);
  LOG(INFO) << "pos: " << pos;
  LOG(INFO) << "num_index: " << num_index;
  LOG(INFO) << "index: " << index;
  LOG(INFO) << "index bit format: " << std::bitset<32>(index);
  LOG(INFO) << "operaion: " << std::bitset<64>((UINT64_C(1) << index));
  LOG(INFO) << "cardinality: " << cardinality;
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  uint64_t word = 1;
  uint16_t pos = 32234;
  bitmap_locate(word, pos);
  return 0;
}
