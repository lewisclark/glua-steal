# For Vim YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include self
include_directories(.)

# file
add_subdirectory(file)

# tests
enable_testing()
add_subdirectory(tests)

# Sources to compile
set(sources main.cpp init.cpp logger.cpp library/library.cpp lua/lualoader.cpp lua/luaexports.cpp
	gamesdk/IVEngineClient.cpp gamesdk/ILuaShared.cpp gamesdk/ILuaInterface.cpp
	hook/luashared.cpp hook/luainterface.cpp)

add_library(gluasteal SHARED ${sources})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only stdc++fs file -m32)
	target_compile_options(gluasteal PRIVATE -Wall -Wextra -pedantic -m32 -Wno-unused-variable)
	set_target_properties(gluasteal PROPERTIES PREFIX "")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} fmt-header-only)
	target_compile_options(gluasteal PRIVATE /W4 /arch:IA32)
endif()
