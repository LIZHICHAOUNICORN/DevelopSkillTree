cmake_minimum_required(VERSION 3.10)

add_executable(add_digits add_digits.cc)
target_link_libraries(add_digits glog gflags_nothreads unwind)
