add_library(lua luaexports.cpp lualoader.cpp luadumper.cpp)

target_link_libraries(lua PRIVATE file)
