set(CMAKE_CXX_FLAGS "-m32 -Wall -Wextra -pedantic -Wno-unused-variable -arch i386")
set(CMAKE_C_FLAGS "-m32 -Wall -Wextra -pedantic -Wno-unused-variable -arch i386")

set(CMAKE_EXE_LINKER_FLAGS "-m32 -arch i386")

set(CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.15/)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")

set(CMAKE_OSX_ARCHITECTURES i386)
