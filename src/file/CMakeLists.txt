add_library(file file.cpp sanitization.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(file PRIVATE stdc++fs)
endif()
