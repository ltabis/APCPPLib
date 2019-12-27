cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(APCPPLib)

# Adding valgrind flags
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-g)
endif()

set(CMAKE_CXX_FLAGS "-Wall -fprofile-arcs -ftest-coverage")

## Enable Google test library
enable_testing()

# Required packages
find_package(Threads)
find_package(GTest REQUIRED)  

set(SRC lib/src/Exception/Exception.cpp
        lib/src/Log/Logger.cpp
        lib/src/Benchmarking/Breakpoint.cpp
        lib/src/Maths/Triangles.cpp)

## Include headers to program
include_directories(
  lib/src/Log
  lib/src/Maths
  lib/src/Utils
  lib/src/Exception
  lib/src/Benchmarking
  include)

## Creating executable
add_executable(APCPPLib
  ${SRC}
  main.cpp)

## Creating executable of unit tests
include(GoogleTest)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)
add_executable(unit_tests
              ${SRC}
              tests/main.cpp
              tests/Exception/test_exception.cpp
              tests/Maths/test_triangles.cpp
              tests/Utils/test_tuples.cpp
	            tests/Log/test_logger.cpp)

  ## Linking libraries
target_link_libraries(APCPPLib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unit_tests PUBLIC
                      ${GTEST_LIBRARIES} pthread
                      ${CMAKE_THREAD_LIBS_INIT})
