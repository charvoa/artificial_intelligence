project(AI_PROJECT)

set(EXECUTABLE_NAME "ai_project")

cmake_minimum_required(VERSION 2.6)

if(CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g3")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Woverloaded-virtual -Wfloat-equal")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wredundant-decls -Wdouble-promotion -Winit-self")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wundef -Winline")
endif(CMAKE_COMPILER_IS_GNUCC)

include_directories(. ./src/ ./header)

add_executable(
  ai_project
  ./src/main.cpp
  ./header/Root.hpp)