cmake_minimum_required (VERSION 2.8)
project (TEST)

add_subdirectory (src)
add_subdirectory (test)

add_executable (demo main.cpp)
target_link_libraries (demo Sqr)

enable_testing()
add_test (NAME MyTest COMMAND Test)
