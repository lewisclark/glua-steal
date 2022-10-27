cmake_minimum_required(VERSION 3.10)
project(gluasteal LANGUAGES CXX VERSION 2.0)

find_library(libSystem "system" "System" "libsystem" "libSystem")

message(STATUS "libSystem: ${libSystem}")

enable_testing()

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

# toml11
include_directories(toml11)

# gluasteal src
add_subdirectory(src)
