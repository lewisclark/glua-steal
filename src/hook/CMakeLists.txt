add_library(hook luainterface.cpp luashared.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(hook PRIVATE -m32 lua file)
	target_compile_options(hook PRIVATE -Wall -Wextra -pedantic -m32 -Wno-unused-variable)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(hook PRIVATE lua file)
	target_compile_options(hook PRIVATE /W4 /arch:IA32)
endif()
