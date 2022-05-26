cmake_minimum_required(VERSION 3.20)
project(YMPThreadsAsync)
include_directories(includes)

set(CMAKE_CXX_STANDARD 20)

add_executable(YMPThreadsAsync main.cpp includes/Timer.h)
