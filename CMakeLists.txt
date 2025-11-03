cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(heaptest)
# Define executable
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(alloc_benchmark src/alloc_common.cpp src/main.cpp)
add_executable(alloc_benchmark_multi src/alloc_common.cpp src/multi_thread_main.cpp)
