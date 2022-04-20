cmake_minimum_required(VERSION 3.21)
project(navigation VERSION "0.1.0")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fexec-charset=GBK")
find_package(Threads)

if (APPLE)
    set(CMAKE_C_COMPILER "/usr/local/bin/gcc-10")
    set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-10")
endif(APPLE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

add_subdirectory(src)
enable_testing()
#add_executable(navigation )
