cmake_minimum_required(VERSION 3.18)
project(devan_yahtzee)

set(CMAKE_CXX_STANDARD 20)

add_executable(devan_yahtzee src/main.cpp src/objects/roll.h src/exceptions/roll.h src/objects/scorecard.h)
add_subdirectory(tst)