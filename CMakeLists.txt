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
  src/main.cpp)

target_link_libraries(APCPPLib ${CMAKE_THREAD_LIBS_INIT})
