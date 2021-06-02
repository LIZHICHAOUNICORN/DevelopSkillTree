cmake_minimum_required(VERSION 3.10)

add_executable(valid_anagram valid_anagram.cc)
target_link_libraries(valid_anagram gflags_nothreads glog unwind)

#add_executable(group_anagrams group_anagrams.cc)
#target_link_libraries(group_anagrams gflags_nothreads glog unwind)

add_executable(two_sum_hashtable two_sum.cc)
target_link_libraries(two_sum_hashtable gflags_nothreads glog unwind)

add_executable(majority_element majority_element.cc)
target_link_libraries(majority_element gflags_nothreads glog unwind)

add_executable(isomorphic_strings isomorphic_strings.cc)
target_link_libraries(isomorphic_strings gflags_nothreads glog unwind)

add_executable(set_mismatch set_mismatch.cc)
target_link_libraries(set_mismatch gflags_nothreads glog unwind)
