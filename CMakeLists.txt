cmake_minimum_required(VERSION 3.31)
project(Backtesting_Engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Backtesting_Engine main.cpp)
