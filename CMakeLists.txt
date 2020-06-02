cmake_minimum_required(VERSION 3.10)
project(gluasteal LANGUAGES CXX VERSION 1.5)

# set PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_definitions(-DGLUASTEAL_VERSION=${gluasteal_VERSION})

# C++ standard
set(CMAKE_CXX_STANDARD 17)

# spdlog
include_directories(spdlog/include)

# glua headers
include_directories(glua_headers/include)

# catch2
include_directories(catch2/single_include)

# gluasteal src
add_subdirectory(src)
