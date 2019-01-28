add_library(file file.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(file PRIVATE stdc++fs -m32)
	target_compile_options(file PRIVATE -Wall -Wextra -pedantic -m32)
	set_target_properties(file PROPERTIES PREFIX "")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(file PRIVATE /W4 /arch:IA32)
endif()
