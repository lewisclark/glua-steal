cmake_minimum_required(VERSION 3.11)
project(gluatake CXX)

# For Vim YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

# libfmt
include_directories(fmt/include)
add_subdirectory(fmt)

# subhook
set(SUBHOOK_STATIC ON)
set(SUBHOOK_FORCE_32BIT ON)
include_directories(subhook)
add_subdirectory(subhook)

# Sources to compile
set(sources main.cpp init.cpp logger.cpp file.cpp library.cpp hook.cpp
	sourcesdk/IVEngineClient.cpp)

add_library(gluatake SHARED ${sources})
target_link_libraries(gluatake fmt-header-only subhook)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(gluatake PRIVATE -Wall -Wextra -m32)
	target_link_options(gluatake PRIVATE -pthread -m32)
	set_target_properties(gluatake PROPERTIES PREFIX "")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(gluatake PRIVATE /W4 /arch:IA32)
endif()
