cmake_minimum_required(VERSION 3.16)
project(Sodoku_Solver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-mpopcnt -O3 -msse4.2")

add_definitions(-fopenmp)

add_executable(Sodoku_Solver main.cpp Board.cpp Board.h Square.cpp Square.h BruteForce.cpp BruteForce.h BoardWrapper.cpp BoardWrapper.h Common.cpp Crooks.cpp Crooks.h Solver.cpp Solver.h BruteForceBasicChecks.cpp BruteForceBasicChecks.h)

find_package(OpenMP REQUIRED)
target_link_libraries(Sodoku_Solver PRIVATE OpenMP::OpenMP_CXX)