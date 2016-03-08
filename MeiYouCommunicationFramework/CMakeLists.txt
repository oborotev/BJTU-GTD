cmake_minimum_required(VERSION 3.3)
project(MeiYouCommunication)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES src/main.cpp)
add_executable(MeiYouCommunication ${SOURCE_FILES})