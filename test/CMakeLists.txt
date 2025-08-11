cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest)
set(gtest_SOURCE_DIR, lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp)