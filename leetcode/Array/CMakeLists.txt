cmake_minimum_required(VERSION 3.10)

add_executable(container_with_most_water container_with_most_water.cc)
target_link_libraries(container_with_most_water glog gflags_nothreads unwind)

add_executable(move_zeroes move_zeroes.cc)
target_link_libraries(move_zeroes gflags_nothreads glog unwind)

add_executable(climbing_stairs climbing_stairs.cc)
target_link_libraries(climbing_stairs unwind gflags_nothreads glog)

add_executable(two_sum two_sum.cc)
target_link_libraries(two_sum unwind gflags_nothreads glog)

add_executable(three_sum three_sum.cc)
target_link_libraries(three_sum unwind gflags_nothreads glog)

add_executable(remove_duplicates remove_duplicates.cc)
target_link_libraries(remove_duplicates unwind gflags_nothreads glog)

add_executable(rotate_array rotate_array.cc)
target_link_libraries(rotate_array unwind gflags_nothreads glog)

add_executable(merge_sorted_array merge_sorted_array.cc)
target_link_libraries(merge_sorted_array unwind gflags_nothreads glog)

add_executable(contains_duplicate contains_duplicate.cc)
target_link_libraries(contains_duplicate unwind gflags_nothreads glog)

add_executable(rotate_image rotate_image.cc)
target_link_libraries(rotate_image unwind gflags_nothreads glog)
