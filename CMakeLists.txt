cmake_minimum_required(VERSION 3.10)

# set the project name
project(Arc VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ox")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(PROJECT_BINARY_DIR, "build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/archive")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

include_directories(${Arc_SOURCE_DIR}/include)
link_directories(${Arc_SOURCE_DIR}/src)

FILE(GLOB src_files src/*.cpp)
ADD_EXECUTABLE(Arc src/arc.cxx ${src_files})
