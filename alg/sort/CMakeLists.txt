cmake_minimum_required(VERSION 3.10)
project(SortChar)

# Set C++ standard, as per project guidelines
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags for debugging and sanitizing, as per project guidelines
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3 -fsanitize=address -fno-omit-frame-pointer")

# Add the current directory to the include path for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library from the source files
add_library(sort_char_lib sort_char.cpp)

# Add subdirectories for command-line, and tests
add_subdirectory(cmd)
# add_subdirectory(tests)
