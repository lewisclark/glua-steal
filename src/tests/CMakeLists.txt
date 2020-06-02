add_executable(tests main.cpp file.cpp)

target_link_libraries(tests PRIVATE file)

add_test(NAME tests COMMAND tests)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(tests PRIVATE)
	target_compile_options(tests PRIVATE -Wall -Wextra -pedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(tests PRIVATE /W4 /arch:IA32)
endif()
