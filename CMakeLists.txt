cmake_minimum_required(VERSION 3.14)

option(BHP_BUILD_TESTS OFF)

project(bit-helper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0077 NEW)

add_library(bit-helper INTERFACE)

target_include_directories(bit-helper INTERFACE "include")

if(EINU_CORE_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(BHP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
