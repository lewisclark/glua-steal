add_library(hook luainterface.cpp luashared.cpp)

target_link_libraries(hook PRIVATE lua file)
