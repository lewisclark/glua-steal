add_library(library library.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(library PRIVATE -m32)
	target_compile_options(library PRIVATE -Wall -Wextra -pedantic -m32 -Wno-unused-variable)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(library PRIVATE /W4 /arch:IA32)
endif()
