# For Vim YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include self
include_directories(.)

# file
add_subdirectory(file)

# lua
add_subdirectory(lua)

# gamesdk
add_subdirectory(gamesdk)

# hook
add_subdirectory(hook)

# library
add_subdirectory(library)

# tests
add_subdirectory(tests)

add_library(gluasteal SHARED main.cpp init.cpp logger.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only file lua hook gamesdk library -m32)
	target_compile_options(gluasteal PRIVATE -Wall -Wextra -pedantic -m32 -Wno-unused-variable)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only)
	target_compile_options(gluasteal PRIVATE /W4 /arch:IA32)
endif()
