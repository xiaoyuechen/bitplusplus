add_executable(bitplusplus-tests "src/bit_tests.cc" "src/bit_vector_test.cc")

target_link_libraries(bitplusplus-tests PRIVATE bitplusplus gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(bitplusplus-tests)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0)

set(INSTALL_GTEST
    OFF
    CACHE BOOL "" FORCE)

if(MSVC)
  # cmake-lint: disable=C0103
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)
