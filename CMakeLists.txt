cmake_minimum_required(VERSION 3.11)
project(gluasteal LANGUAGES CXX VERSION 1.0)

add_definitions(-DGLUASTEAL_VERSION=${gluasteal_VERSION})

# For Vim YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

# threads
find_package(Threads)

# libfmt
include_directories(fmt/include)
add_subdirectory(fmt)

# glua headers
include_directories(glua_headers/include)

# Sources to compile
set(sources main.cpp init.cpp logger.cpp file.cpp library.cpp hook.cpp
	sourcesdk/IVEngineClient.cpp)

add_library(gluasteal SHARED ${sources})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only subhook stdc++fs)
	target_compile_options(gluasteal PRIVATE -Wall -Wextra -pedantic -m32)
	target_link_options(gluasteal PRIVATE -m32)
	set_target_properties(gluasteal PROPERTIES PREFIX "")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only subhook)
	target_compile_options(gluasteal PRIVATE /W4 /arch:IA32)
endif()
