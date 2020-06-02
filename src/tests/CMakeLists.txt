add_executable(tests main.cpp file.cpp)

target_link_libraries(tests PRIVATE file)

add_test(NAME tests COMMAND tests)
