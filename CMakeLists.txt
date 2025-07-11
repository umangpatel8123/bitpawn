cmake_minimum_required(VERSION 3.10)
project(bitpawn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Add source files recursively from src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(bitpawn ${SOURCES})
