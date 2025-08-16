cmake_minimum_required(VERSION 3.31)
project(ActivityTracker)

set(CMAKE_CXX_STANDARD 20)

set(NCURSES_INCLUDE "C:/MinGW/include/ncurses")
set(NCURSES_LIB "C:/MinGW/lib/libncurses.a")
set(SOURCE_FILES Activity.cpp)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})

add_subdirectory(test)

include_directories(${NCURSES_INCLUDE})
target_link_libraries(${CMAKE_PROJECT_NAME} ${NCURSES_LIB} ${CMAKE_PROJECT_NAME}_lib)