cmake_minimum_required(VERSION 3.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Arc)

set(PROJECT_BINARY_DIR, "build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/archive")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

ADD_EXECUTABLE(arc ${Arc_SOURCE_DIR}/src/executables/arc.cpp)
target_include_directories(arc PUBLIC ${Arc_SOURCE_DIR}/include/exceptions)

add_subdirectory(src)

## TESTS ##

enable_testing()
add_test(NAME leo_propagation COMMAND $<TARGET_FILE:arc> ${Arc_SOURCE_DIR}/tests/propagation_leo.json WORKING_DIRECTORY ${Arc_SOURCE_DIR})