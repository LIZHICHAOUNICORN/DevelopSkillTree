cmake_minimum_required(VERSION 3.10)

project(arsenal C CXX)

# Release/Debug 使用gdb 调试时应该用Debug
# 上线服务使用Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAGS
 -W
 -Wall
 -Werror
 -Wno-unused-parameter
)

# 注意： mac os C++11 标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -L/usr/local/lib")

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
# bug: when use -DNDEBUG and set release version, the error:
# gmock declared ‘static’ but never defined [-Werror=unused-function]
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

find_package(Threads)

# add_subdirectory(third_party/libevent)
add_subdirectory(third_party/glog)
add_subdirectory(third_party/gflags)
# add_subdirectory(third_party/muduo)
# add_subdirectory(third_party/googletest)
# add_subdirectory(third_party/googleurl)
# add_subdirectory(third_party/abseil-cpp)

add_subdirectory(leetcode)
# add_subdirectory(codelab)
# add_subdirectory(search)

include_directories(third_party)
