cmake_minimum_required(VERSION 3.18)
project(devan_yahtzee)

set(CMAKE_CXX_STANDARD 20)

add_executable(devan_yahtzee devan-yahtzee/src/main.cpp devan-yahtzee/src/objects/roll.h tst/roll_tests.cpp)
add_subdirectory(tst)