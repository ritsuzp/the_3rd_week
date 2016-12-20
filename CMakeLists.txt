cmake_minimum_required(VERSION 3.6)
project(task_trajectory_generator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(task_trajectory_generator ${SOURCE_FILES})