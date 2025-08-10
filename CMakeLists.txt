cmake_minimum_required(VERSION 3.31)
project(ActivityTracker)

add_subdirectory(test)

set(CMAKE_CXX_STANDARD 20)

set(NCURSES_INCLUDE "C:/MinGW/include/ncurses")
set(NCURSES_LIB "C:/MinGW/lib/libncurses.a")

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

include_directories(${NCURSES_INCLUDE})
target_link_libraries(${CMAKE_PROJECT_NAME} ${NCURSES_LIB})