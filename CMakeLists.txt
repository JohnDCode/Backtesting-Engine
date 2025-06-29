cmake_minimum_required(VERSION 3.31)
project(Backtesting_Engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Step 1: Build C++ engine as a static library
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS src/engine/*.cpp)
add_library(backtest_lib STATIC ${ENGINE_SRC})
target_include_directories(backtest_lib PUBLIC include)

# Step 2: Optional C++ executable for testing
add_executable(Backtesting_Engine main.cpp)
target_link_libraries(Backtesting_Engine PRIVATE backtest_lib)

# Step 3: Add pybind11 module
add_subdirectory(extern/pybind11)

pybind11_add_module(backtest_python bindings/bindings.cpp)
target_include_directories(backtest_python PRIVATE include)
target_link_libraries(backtest_python PRIVATE backtest_lib)