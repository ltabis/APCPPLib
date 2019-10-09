cmake_minimum_required(VERSION 3.14)
project(APCPPLib)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        lib/src/Exception
        include)

add_executable(APCPPLib
        lib/src/Exception/Exception.cpp
        src/main.cpp)
