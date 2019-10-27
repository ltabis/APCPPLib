cmake_minimum_required(VERSION 3.14)
project(APCPPLib)

find_package(Threads)
set(CMAKE_CXX_STANDARD 14)

include_directories(
  lib/src/Exception
  lib/src/Log
  include)

add_executable(APCPPLib
  lib/src/Exception/Exception.cpp
  lib/src/Log/Logger.cpp
  src/main.cpp)

target_link_libraries(APCPPLib ${CMAKE_THREAD_LIBS_INIT})