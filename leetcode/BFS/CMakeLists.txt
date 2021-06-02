cmake_minimum_required(VERSION 3.10)

add_executable(bfs_template bfs_template.cc)
target_link_libraries(bfs_template gflags_nothreads glog unwind)

add_executable(minimum_genetic_mutation minimum_genetic_mutation.cc)
target_link_libraries(minimum_genetic_mutation gflags_nothreads glog unwind)

add_executable(word_ladder word_ladder.cc)
target_link_libraries(word_ladder gflags_nothreads glog unwind)

add_executable(word_ladder_ii word_ladder_ii.cc)
target_link_libraries(word_ladder_ii gflags_nothreads glog unwind)
