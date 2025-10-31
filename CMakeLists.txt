set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(heaptest)
# Define executable
add_executable(alloc_benchmark src/main.cpp)
