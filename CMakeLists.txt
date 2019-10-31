cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
project(APCPPLib)

add_compile_options(-g)
find_package(Threads)

include_directories(
  lib/src/Exception
  lib/src/Log
  lib/src/Benchmarking
  include)

add_executable(APCPPLib
  lib/src/Exception/Exception.cpp
  lib/src/Log/Logger.cpp
  lib/src/Benchmarking/Breakpoint.cpp
  main.cpp)

add_custom_target(unit_tests ALL
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/
  COMMAND make
)

target_link_libraries(APCPPLib ${CMAKE_THREAD_LIBS_INIT})
