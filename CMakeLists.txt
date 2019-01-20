cmake_minimum_required(VERSION 3.11)
project(gluatake CXX)

# For Vim YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

# libfmt
include_directories(fmt/include)
add_subdirectory(fmt)

# Sources to compile
set(sources main.cpp init.cpp)

add_library(gluatake SHARED ${sources})
target_link_libraries(gluatake fmt)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(gluatake PRIVATE -Wall -Wextra)
	target_link_options(gluatake PRIVATE -pthread)
	set_target_properties(gluatake PROPERTIES PREFIX "")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	message("Identified that you are using MSVC")

	target_compile_options(gluatake PRIVATE /W4)
endif()
