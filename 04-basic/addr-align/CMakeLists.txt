cmake_minimum_required(VERSION 3.1)
project(mem_align)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")

set(SOURCE_FILES main.cpp)
add_executable(mem_align ${SOURCE_FILES})
