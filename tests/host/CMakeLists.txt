# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

project(host_tests C CXX ASM)

# # Set up variables for directories
set(HOST_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR})
set(HOST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Include tests directory as subdirectory
add_subdirectory(average)