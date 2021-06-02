cmake_minimum_required(VERSION 3.10)

add_executable(dfs_template dfs_template.cc)
target_link_libraries(dfs_template gflags_nothreads glog unwind)

add_executable(binary_tree_paths binary_tree_paths.cc ../Tree/tree_node.h)
target_link_libraries(binary_tree_paths gflags_nothreads glog unwind)
