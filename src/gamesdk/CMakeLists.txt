add_library(gamesdk ILuaInterface.cpp ILuaShared.cpp IVEngineClient.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(gamesdk PRIVATE -m32)
	target_compile_options(gamesdk PRIVATE -Wall -Wextra -pedantic -m32 -Wno-unused-variable)
	set_target_properties(gamesdk PROPERTIES PREFIX "")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(gamesdk PRIVATE /W4 /arch:IA32)
endif()
