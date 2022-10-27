set(CMAKE_CXX_FLAGS "-lSystem -m32 -Wall -Wextra -pedantic -Wno-unused-variable")
set(CMAKE_C_FLAGS "-lSystem -m32 -Wall -Wextra -pedantic -Wno-unused-variable")

set(CMAKE_EXE_LINKER_FLAGS "-lSystem -m32")

add_link_options("-lSystem")
