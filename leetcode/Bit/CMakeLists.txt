cmake_minimum_required(VERSION 3.10)

add_executable(number_of_1_bits number_of_1_bits.cc)
target_link_libraries(number_of_1_bits glog gflags_nothreads unwind)

add_executable(power_of_two power_of_two.cc)
target_link_libraries(power_of_two glog gflags_nothreads unwind)
