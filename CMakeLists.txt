cmake_minimum_required(VERSION 3.11)
project(gluatake)

# For Vim YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# libfmt
include_directories(fmt/include)
add_subdirectory(fmt)

# Sources to compile
set(sources main.cpp)

add_library(gluatake SHARED ${sources})
target_link_libraries(gluatake fmt)
set_target_properties(gluatake PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wextra -g" LINK_FLAGS "")
