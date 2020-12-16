cmake_minimum_required(VERSION 3.14)

option(BPP_BUILD_TESTS OFF)

project(bitplusplus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0077 NEW)

add_library(bitplusplus INTERFACE)

target_include_directories(bitplusplus INTERFACE "include")

if(BPP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
