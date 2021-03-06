cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(APCPPLib VERSION 0.5.0 DESCRIPTION "A library designed to help you during the developpement of your C++ projects")

## Conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Enable Google test library
enable_testing()

# Required packages
find_package(Threads)

# source files
set(SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Exception/Exception.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Log/Logger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Benchmarking/Breakpoint.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Maths/Triangles.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Utils/LibraryLoader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Game/SceneStateMachine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Game/AScene.cpp
)

# Include headers to program
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Log
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Game
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Maths
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Utils
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Exception
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Algorithm
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/Benchmarking
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Creating the library
add_library(APCPPLib STATIC ${SRC})

# Set library version
set_target_properties(APCPPLib PROPERTIES VERSION ${PROJECT_VERSION})

# Creating executable of unit tests
include(GoogleTest)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)

add_executable(unit_tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Exception/test_exception.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Maths/test_triangles.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Utils/test_tuples.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Log/test_logger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Game/test_sceneStateMachine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/Algorithm/test_bubbleSort.cpp
)

## Linking libraries
target_link_libraries(APCPPLib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unit_tests PUBLIC
  APCPPLib
  CONAN_PKG::gtest
  ${CMAKE_THREAD_LIBS_INIT}
)
