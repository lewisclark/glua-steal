cmake_minimum_required(VERSION 3.10)
project(gluasteal LANGUAGES CXX VERSION 1.2)

add_definitions(-DGLUASTEAL_VERSION=${gluasteal_VERSION})

# For Vim YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ standard
set(CMAKE_CXX_STANDARD 17)

# include self
include_directories(.)

# threads
find_package(Threads)

# libfmt
include_directories(fmt/include)
add_subdirectory(fmt)

# tests
enable_testing()
add_subdirectory(tests)

# glua headers
include_directories(glua_headers/include)

# Sources to compile
set(sources main.cpp init.cpp logger.cpp file.cpp library/library.cpp lua/lualoader.cpp lua/luaexports.cpp
	gamesdk/IVEngineClient.cpp gamesdk/ILuaShared.cpp gamesdk/ILuaInterface.cpp
	hook/luashared.cpp hook/luainterface.cpp)

add_library(gluasteal SHARED ${sources})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only stdc++fs -m32)
	target_compile_options(gluasteal PRIVATE -Wall -Wextra -pedantic -m32 -Wno-unused-variable)
	set_target_properties(gluasteal PROPERTIES PREFIX "")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only)
	target_compile_options(gluasteal PRIVATE /W4 /arch:IA32)
endif()
