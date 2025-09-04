cmake_minimum_required(VERSION 3.28)
project(ActivityTracker)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES Activity.cpp Register.cpp Utils.cpp)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})

add_subdirectory(test)

target_link_libraries(${CMAKE_PROJECT_NAME} fltk fltk_images ${CMAKE_PROJECT_NAME}_lib)