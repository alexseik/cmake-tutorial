find_package(Boost 1.56.0 COMPONENTS unit_test_framework REQUIRED)

include_directories (${TEST_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS})

#add_definitions (-DBOOST_TEST_DYN_LINK)

add_executable (TestSqr test.cpp )
add_executable (TestQueryTranslate queryTranslateTest.cpp)

target_link_libraries(TestSqr Sqr ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY})

target_link_libraries(TestQueryTranslate QueryTranslate ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY})
