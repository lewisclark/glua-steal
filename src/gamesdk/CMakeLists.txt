add_library(gamesdk ILuaInterface.cpp ILuaShared.cpp IVEngineClient.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(gamesdk PRIVATE)
	target_compile_options(gamesdk PRIVATE -Wall -Wextra -pedantic -Wno-unused-variable)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(gamesdk PRIVATE /W4 /arch:IA32)
endif()
