cmake_minimum_required (VERSION 2.8)
project (TEST)

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	set(BOOST_ROOT "/home/alexseik/app/boost_1_57_0")
	set(Boost_INCLUDE_DIR "/home/alexseik/app/boost_1_57_0")
endif()

if (MSVC10)
	set(BOOST_ROOT "C:\\local\\boost_1_57_0")
	set(Boost_INCLUDE_DIR "C:\\local\\boost_1_57_0")
	#set(Boost_USE_STATIC_LIBS OFF)
	#set(Boost_USE_MULTITHREADED ON)
	#set(Boost_USE_STATIC_RUNTIME OFF)
endif()

add_subdirectory (src)
add_subdirectory (test)

include_directories (${TEST_SOURCE_DIR}/src)
message("${TEST_SOURCE_DIR}")
add_executable (demo main.cpp)
target_link_libraries (demo Sqr)

enable_testing()
add_test (NAME SqrTest COMMAND TestSqr)
add_test (NAME QueryTranslateTest COMMAND TestQueryTranslate)
