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

target_link_libraries(gluasteal PRIVATE ${CMAKE_THREADS_LIBS_INIT} file lua hook gamesdk library)
