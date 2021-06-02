cmake_minimum_required(VERSION 3.10)

add_executable(group_anagrams group_anagrams.cc)
target_link_libraries(group_anagrams gflags_nothreads glog unwind)
