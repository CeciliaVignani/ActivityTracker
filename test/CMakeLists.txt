cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest)
set(gtest_SOURCE_DIR lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp ActivityTest.cpp RegisterTest.cpp)
add_executable(tests ${TEST_SOURCE_FILES})
target_link_libraries(tests gtest ${CMAKE_PROJECT_NAME}_lib)