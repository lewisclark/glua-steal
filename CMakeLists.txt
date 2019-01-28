cmake_minimum_required(VERSION 3.10)
project(gluasteal LANGUAGES CXX VERSION 1.2)

add_definitions(-DGLUASTEAL_VERSION=${gluasteal_VERSION})

# C++ standard
set(CMAKE_CXX_STANDARD 17)

# libfmt
include_directories(fmt/include)
add_subdirectory(fmt)

# glua headers
include_directories(glua_headers/include)

# gluasteal src
add_subdirectory(src)
