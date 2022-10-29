set(CMAKE_CXX_FLAGS "-lSystem -m32 -Wall -Wextra -pedantic -Wno-unused-variable -arch i386")
set(CMAKE_C_FLAGS "-lSystem -m32 -Wall -Wextra -pedantic -Wno-unused-variable -arch i386")

set(CMAKE_EXE_LINKER_FLAGS "-lSystem -m32 -arch i386")

add_link_options("-lSystem")
