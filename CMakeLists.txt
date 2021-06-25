cmake_minimum_required(VERSION 3.18)
project(devan_yahtzee)

set(CMAKE_CXX_STANDARD 20)

add_executable(devan_yahtzee src/main.cpp src/state_objects/roll.h tst/roll_tests.cpp src/exceptions/roll.h src/exceptions/scorecard.h src/state_objects/box.h)
add_subdirectory(tst)