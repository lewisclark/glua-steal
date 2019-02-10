add_library(lua luaexports.cpp lualoader.cpp luadumper.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(lua PRIVATE -m32 file)
	target_compile_options(lua PRIVATE -Wall -Wextra -pedantic -m32 -Wno-unused-variable)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(lua PRIVATE file)
	target_compile_options(lua PRIVATE /W4 /arch:IA32)
endif()
