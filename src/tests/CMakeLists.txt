add_executable(tests main.cpp file.cpp config.cpp ../config.cpp ../logger.cpp)

target_link_libraries(tests PRIVATE file)

add_test(NAME tests COMMAND tests)
